<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
    
<html>
<head>
	<title>MBlog|首页</title>
</head>

<body>
	<%
	request.setCharacterEncoding("utf-8");
	String uid = (String)session.getAttribute("uid");
	String email = (String)session.getAttribute("email");
	String username = (String)session.getAttribute("username");
	String is_valid = (String)session.getAttribute("is_valid");
	if (uid == null) {
	%>
	<div style="float:right">
		<form action="register.jsp" method="post">
			<input type="submit" name="register" value="注册">
		</form>
		<form action="login.jsp" method="post">
			<input type="submit" name="login" value="登录">
		</form>
	</div>
	<%
	} else {
	%>
	<div style="float:right">
		<%=username%>, 欢迎您!
		<form action="status.jsp" method="post">
			<input type="submit" name="status" value="个人中心">
		</form>
		<form action="add.jsp" method="post">
			<input type="submit" name="logoff" value="创建博客">
		</form>
		<form action="logoff.jsp" method="post">
			<input type="submit" name="logoff" value="退出登录">
		</form>
	</div>
	<%
	}
	%><h1>MBLOG, 不只是BLOG</h1><%
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
    	sql_user = con.createStatement();
    	rs = sql.executeQuery("SELECT * FROM blog;");
    	while(rs.next()) {
    		rs_user = sql_user.executeQuery("SELECT * FROM user WHERE uid="+Integer.toString(rs.getInt("uid"))+";");
    		rs_user.next();
    		out.println("<h2>" + rs.getString("title") + "</h2>");
    		out.println("<p>作者:"+rs_user.getString("name")+" | 时间:"+rs.getString("time")+"</p>");
    		out.println("<p>" + rs.getString("text") + "</p><br>");
    	}
    	sql.close();
    	con.close();
	}
	catch(SQLException e1) { out.print(e1); }
	%>
</body>

</html>