<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
<%@ page import="tom.jiafei.QueryBeanOne" %>
<%@ page import="tom.jiafei.AddBean" %>
<jsp:useBean id="look" class="tom.jiafei.QueryBeanOne" scope="request" />
<jsp:useBean id="add" class="tom.jiafei.AddBean" scope="request" />
<jsp:setProperty  name= "look"  property="ODBCDataSource" value="mblog" />
<jsp:setProperty  name= "look"  property="tableName" value="blog" />
<jsp:setProperty  name= "look"  property="user" value="root" />
<jsp:setProperty  name= "look"  property="secret" value="989800" />

<html>
<head>
<title>查询MBlog</title>
</head>

<body>
	<%
		String bid = request.getParameter("bid");
		out.println("BlogID:" + bid + " 查询结果:");
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
       		rs = sql.executeQuery("select * from blog where bid =" + bid);
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

</body>

</html>
<!-- MegaShow -->