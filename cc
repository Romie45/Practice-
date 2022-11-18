java with maven 

pool
driverClass   com.mysql.cj.jdbc.Driver
port
ServerName
User
Password
url 
URL jdbc:mysql://localhost:3306/garmentdb
driverClass  com.mysql.cj.jdbc.Driver

DATABASE TABLE CONNECT

=========================================  MSAapp  ===========================================

right click project> property: run paya server

1. Entity: entity from database

changes in entities:

@JsonbTransient  === above all getall collection & get garmentid

garments with 1fk category:

@NamedQuery(name = "Garments.findAll", query = "SELECT g FROM Garments g WHERE NOT g.stock = 0")
@NamedQuery(name ="Garments.findbycategory", query = "SELECT g FROM Garments g WHERE g.categoryid = :categoryid AND NOT g.stock = 0")


2.  Persistence
create datasorce > jdbc/external_data  ...........&   database connection ........... strategy none


3.SessionBean

public class garmentsbean {
    
    @PersistenceContext(unitName = "com.external_EXTERNAL_EXAM_war_1.0-SNAPSHOTPU2")
    EntityManager em;

    public Collection<Garments> getallgarments(){
        return em.createNamedQuery("Garments.findAll").getResultList();
    }
    
    public Collection<Garments> getgarmentsbycategory(Integer categoryid){
        Category cat = em.find(Category.class, categoryid);
        return em.createNamedQuery("Garments.findbycategory").setParameter("categoryid", cat).getResultList();
    }
    
    public Collection<Category> getallcategories(){
        return em.createNamedQuery("Category.findAll").getResultList();
    }
}


4. Example Service:

 @Inject garmentsbean gb;

    @GET
    public Response get() {
        return Response.ok("Hello, world!").build();
    }
    
    @RolesAllowed("CUSTOMER")
    @GET
    @Path("getallgarments")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getallgarments(){
        return gb.getallgarments();
    }
    
    @RolesAllowed("CUSTOMER")
    @GET
    @Path("getbycategory?category={id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getgarmentsbycategory(@PathParam("id")Integer categoryid){
        return gb.getgarmentsbycategory(categoryid);
    }
    
    @RolesAllowed("CUSTOMER")
    @GET
    @Path("getallcategories")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Category> getallcategories(){
        return gb.getallcategories();
    }


5. pom.xml 

 <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>5.1.23</version>
        </dependency>

6.  java -jar payara-micro-5.2022.2.jar --deploy ExamGarments/artifact/ExamGarments.war --port 8085

7.  http://localhost:8085/ExamGarments/rest/example/getallgarments



=========================================  MSAClient  ===========================================




