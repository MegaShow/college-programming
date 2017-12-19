<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>

<html>
<head>
<title>全部MBlog</title>
</head>

<body>
	<p>所有的MBlog信息:</p>
	<%
		Connection con;
      	Statement sql, sql_user; 
      	ResultSet rs, rs_user;
       	try {
       		Class.forName("com.mysql.jdbc.Driver");   
        }
       	catch(Exception e){out.print(e);} 
      	try {  
    	   	String uri = "jdbc:mysql://localhost:3306/mblog";
    	   	String user = "root";
           	String password = "989800";
           	con = DriverManager.getConnection(uri, user, password);
           	sql = con.createStatement();
           	rs = sql.executeQuery("select * from blog;");
            out.print("<table border=2>");
            out.print("<tr>");
            out.print("<th width=100>" + "BlogID");
            out.print("<th width=100>" + "作者");
            out.print("<th width=150>" + "标题");
            out.print("<th width=200>" + "正文");
            out.print("<th width=180>" + "发布时间");
            out.print("<th width=180>" + "修改时间");
            out.print("</TR>");
            while(rs.next()) {
               	sql_user = con.createStatement();
            	rs_user = sql_user.executeQuery("select uname from user where uid =" + rs.getString("author"));
            	rs_user.next();
               	out.print("<tr>");
               	out.print("<td >" + rs.getInt("bid") + "</td>"); 
               	out.print("<td >" + rs_user.getString("uname") + "</td>");
               	out.print("<td >" + rs.getString("title") + "</td>"); 
               	out.print("<td >" + rs.getString("text") + "</td>");
               	out.print("<td >" + rs.getString("time") + "</td>");
               	out.print("<td >" + rs.getString("modify_time") + "</td>");
               	out.print("</tr>") ; 
            }
            out.print("</table>");
            con.close();
      	}
      	catch(SQLException e1) { out.print(e1); }
	%>
	
	<p>通过BlogID查询MBlog信息:</p>
	<form action="findblog.jsp" method="post">
		<input type="text" name="bid">
		<input type="submit" value="查询" name="submit">
	</form>
</body>

</html>
<!-- MegaShow -->