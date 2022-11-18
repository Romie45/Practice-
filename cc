java with maven 
group id ===> com.external

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
    //@RolesAllowed("CUSTOMER")
    @GET
    @Path("getallgarments")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getallgarments(){
        return gb.getallgarments();
    }
    //@RolesAllowed("CUSTOMER")
    @GET
    @Path("getbycategory?category={id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getgarmentsbycategory(@PathParam("id")Integer categoryid){
        return gb.getgarmentsbycategory(categoryid);
    }
    //@RolesAllowed("CUSTOMER")
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

7.  http://localhost:8085/ExamGarments/rest/example/getallgarments  in chrome



=========================================  MSAClient  ===========================================

1. Entity copy from app

2. Interface ===>  RemoteClient
@RegisterRestClient(baseUri = "http://localhost:8085/ExamGarments/rest/example")
public interface RemoteClient {
    
    //@ClientHeaderParam(name="authorization", value="Bearer eyJraWQiOiJqd3Qua2V5IiwidHlwIjoiSldUIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJkdWtlIiwidXBuIjoiZHVrZSIsImF1dGhfdGltZSI6MTY2ODc1Mzc4MywiaXNzIjoiYWlyaGFja3MiLCJncm91cHMiOlsiQ1VTVE9NRVIiXSwiZXhwIjoxNjY4ODUzNzgzLCJpYXQiOjE2Njg3NTM3ODMsImp0aSI6IjQyIn0.Lzfs6TscEfK_HbW6NMO_q-zV8JZYCFMDsTkmz-xL53azv9WkHmOgCAZXH15Zy6msAVxmSvH3vbiHJqZYNT5thaeeOK7oyTVYyNQzMjdBS46MJJabmwQBTg7j3J7pfkBlH1Koe4N1abB2LlPlREf-hhV_bPW1ejMQXdZ0C5Jriw5uYXhiOQWa6pwxsNn-oimcjVKa0ACAvLFzFV47WJr7bE3-8268mcqLo3ZmQVOFaiqwW0iBr2O6vhLNVO-uBA2T9S2SW_eXfWHy1qeI68Uf9GqrwSeFwBdelOX9emc26nQa7z2_t6Lwct_y5eK6kvrvmYcauZcAIqqrE4UX2WtulQ")
    @GET
    @Path("getallgarments")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getallgarments();
    
    //@ClientHeaderParam(name="authorization", value="Bearer eyJraWQiOiJqd3Qua2V5IiwidHlwIjoiSldUIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJkdWtlIiwidXBuIjoiZHVrZSIsImF1dGhfdGltZSI6MTY2ODc1Mzc4MywiaXNzIjoiYWlyaGFja3MiLCJncm91cHMiOlsiQ1VTVE9NRVIiXSwiZXhwIjoxNjY4ODUzNzgzLCJpYXQiOjE2Njg3NTM3ODMsImp0aSI6IjQyIn0.Lzfs6TscEfK_HbW6NMO_q-zV8JZYCFMDsTkmz-xL53azv9WkHmOgCAZXH15Zy6msAVxmSvH3vbiHJqZYNT5thaeeOK7oyTVYyNQzMjdBS46MJJabmwQBTg7j3J7pfkBlH1Koe4N1abB2LlPlREf-hhV_bPW1ejMQXdZ0C5Jriw5uYXhiOQWa6pwxsNn-oimcjVKa0ACAvLFzFV47WJr7bE3-8268mcqLo3ZmQVOFaiqwW0iBr2O6vhLNVO-uBA2T9S2SW_eXfWHy1qeI68Uf9GqrwSeFwBdelOX9emc26nQa7z2_t6Lwct_y5eK6kvrvmYcauZcAIqqrE4UX2WtulQ")
    @GET
    @Path("getbycategory?category={id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Garments> getgarmentsbycategory(@PathParam("id")Integer categoryid);
    
    //@ClientHeaderParam(name="authorization", value="Bearer eyJraWQiOiJqd3Qua2V5IiwidHlwIjoiSldUIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJkdWtlIiwidXBuIjoiZHVrZSIsImF1dGhfdGltZSI6MTY2ODc1Mzc4MywiaXNzIjoiYWlyaGFja3MiLCJncm91cHMiOlsiQ1VTVE9NRVIiXSwiZXhwIjoxNjY4ODUzNzgzLCJpYXQiOjE2Njg3NTM3ODMsImp0aSI6IjQyIn0.Lzfs6TscEfK_HbW6NMO_q-zV8JZYCFMDsTkmz-xL53azv9WkHmOgCAZXH15Zy6msAVxmSvH3vbiHJqZYNT5thaeeOK7oyTVYyNQzMjdBS46MJJabmwQBTg7j3J7pfkBlH1Koe4N1abB2LlPlREf-hhV_bPW1ejMQXdZ0C5Jriw5uYXhiOQWa6pwxsNn-oimcjVKa0ACAvLFzFV47WJr7bE3-8268mcqLo3ZmQVOFaiqwW0iBr2O6vhLNVO-uBA2T9S2SW_eXfWHy1qeI68Uf9GqrwSeFwBdelOX9emc26nQa7z2_t6Lwct_y5eK6kvrvmYcauZcAIqqrE4UX2WtulQ")
    @GET
    @Path("getallcategories")
    @Produces(MediaType.APPLICATION_JSON)
    public Collection<Category> getallcategories();
}

3. Servlet  ====>  RemoteServlet

public class RemoteServlet extends HttpServlet {
    @Inject @RestClient RemoteClient rc;
.
.
throws ServletException, IOException {
        Collection<Garments> gb = rc.getallgarments();
.
.
 for(Garments g: gb){
                if(g.getOrdersCollection().stream().findFirst().isPresent()){
                    Customer cust = g.getOrdersCollection().stream().findFirst().get().getCustomerid();
                    out.println("<p>Garment ID: " + g.getGarmentid() + "</p>");
                    out.println("<p>Category: " + g.getCategoryid().getCategoryname() + "</p>");
                    out.println("<p>Price: " + g.getPrice() +"</p>" );
                    out.println("<p>Customer Name: " + cust.getCustomerName() + "</p>");
                    out.println("<p>Customer Phone: " + cust.getMobile() + "</p>");
                    out.println("<p>Customer City: " + cust.getCity() + "</p>");
                }
            }
option 2 servlets Extrass

=========  Result servlet

try ( PrintWriter out = response.getWriter()) {
            Integer categoryid = Integer.parseInt(request.getParameter("category"));      
            Collection<Garments> getgarments = rc.getgarmentsbycategory(categoryid);
.
.
.
for(Garments g: getgarments){
                if(g.getOrdersCollection().stream().findFirst().isPresent()){
                    Customer c = g.getOrdersCollection().stream().findFirst().get().getCustomerid();
                    out.println("<p>Garment ID: "+g.getGarmentid()+"</p>");
                    out.println("<p>Category: "+g.getCategoryid().getCategoryname()+"</p>");
                    out.println("<p>Price: "+g.getPrice()+"</p>");
                    out.println("<p>Customer Name: "+c.getCustomerName()+"</p>");
                    out.println("<p>Mobile No: "+c.getMobile()+"</p>");
                    Date date = g.getOrdersCollection().stream().findFirst().get().getDate();
                    String OrderDate = DateFormat.getDateInstance().format(date);
                    out.println("<p>Order Date: "+OrderDate+"</p>");
                    out.println("<p>City: "+c.getCity()+"</p>");
                }else{
                    out.println("<p>Garment ID: "+g.getGarmentid()+"</p>");
                    out.println("<p>Category: "+g.getCategoryid().getCategoryname()+"</p>");
                    out.println("<p>Price: "+g.getPrice()+"</p>");
                }
            }

================  RemoteServlet
try ( PrintWriter out = response.getWriter()) {
            Collection<Category> categories = rc.getallcategories();
.
.
out.println("<form action='ResultServlet'>");
            out.println("<select name='category'>");
            for(Category c: categories){
                out.println("<option value='"+c.getCategoryid()+"' label='"+c.getCategoryname()+"'>"+"</option>");
            }
            out.println("</select>");
            out.println("<input type='submit' />");
            out.println("</form>");

4. java -jar payara-micro-5.2022.2.jar --deploy ExamGarmentsClient/artifact/ExamGarmentsClient.war --port 8087
5. http://localhost:8087/ExamGarmentsClient/RemoteServlet

================================  jwt

----------MSAApp
1.  java -jar jwtenizr.jar  -->terminal
2.  property file:-  microprofile-config==>  copy pate property filegenerated
3.  Bootstrap
    @LoginConfig(authMethod = "MP-JWT")
    @DeclareRoles({"CUSTOMER"})
4.  Example Service-------  @RolesAllowed("CUSTOMER")  for each method

----------MSAClient
1. interface ==RemoteClient   @ClientHeaderParam(name="authorization", value="Bearer eyt2I-Nd4n03GT-82MbUVJHa3YcL4lM9iw")  token paste  for each method
   
java -jar payara-micro-5.2022.2.jar --deploy ExamGarments/artifact/ExamGarments.war --port 8085  --> http://localhost:8085/ExamGarments/rest/example/getallgarments
java -jar payara-micro-5.2022.2.jar --deploy ExamGarmentsClient/artifact/ExamGarmentsClient.war --port 8087   -->http://localhost:8087/ExamGarmentsClient/RemoteServlet
