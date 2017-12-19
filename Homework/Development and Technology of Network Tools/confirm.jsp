<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
    
<html>
<head>
	<title>MBlog|认证</title>
</head>

<body style="text-align:center">
	<%
	request.setCharacterEncoding("utf-8");
	String uid = (String)session.getAttribute("uid");
	String email = (String)session.getAttribute("email");
	String username = (String)session.getAttribute("username");
	String is_valid = (String)session.getAttribute("is_valid");
	String bid = request.getParameter("bid");
	if (uid == null) {
		out.println("请先登录后操作!");
		%>
		<form action="login.jsp" method="post">
			<input type="submit" name="submit" value="登录">
		</form>
		<%
	} else {
		String token = request.getParameter("token");
		if (username.equals(token)) {
			Connection con;
	    	Statement sql; 
	    	ResultSet rs;
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
	        	sql.executeUpdate("UPDATE `mblog`.`user` SET `is_valid`='1' WHERE `uid`='"+ uid +"';");
	        	sql.close();
	        	con.close();
	        	session.setAttribute("is_valid", "1");
	        	response.sendRedirect("status.jsp");
	    	}
	    	catch(SQLException e1) { out.print(e1); }
		} else {
			out.println("请求非法!");
		}
	}
	%>
</body>

</html>