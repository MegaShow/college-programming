<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
    
<html>
<head>
	<title>MBlog|写博客</title>
</head>

<body style="text-align:center">
	<%
	request.setCharacterEncoding("utf-8");
	String uid = (String)session.getAttribute("uid");
	String email = (String)session.getAttribute("email");
	String username = (String)session.getAttribute("username");
	String is_valid = (String)session.getAttribute("is_valid");
	String title = request.getParameter("title");
	String text = request.getParameter("text");
	if (uid == null) {
		out.println("请先登录后操作!");
		%>
		<form action="login.jsp" method="post">
			<input type="submit" name="submit" value="登录">
		</form>
		<%
	} else if (title == null) {
		%>
		<form method="post">
			<input type="text" name="title" value="标题"><br>
			<textarea name="text" cols="30" rows="5">正文</textarea><br>
			<input type="submit" name="submit" value="创建Blog"><br>
		</form>
		<%
	} else {
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
       		String pwd = "989800";
       		con = DriverManager.getConnection(uri, user, pwd);
       		sql = con.createStatement();
       		rs = sql.executeQuery("select * from globe where id=2");
       		rs.next();
       		int bid = rs.getInt("value") + 1;
       		java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
       		java.util.Date currentTime = new java.util.Date();//得到当前系统时间
       		String date = formatter.format(currentTime); //将日期时间格式化 
       		sql.executeUpdate("UPDATE `mblog`.`globe` SET `value`='"+bid+"' WHERE `id`='2';");
        	sql.executeUpdate("INSERT INTO `mblog`.`blog`(`bid`,`uid`,`title`,`text`,`time`)VALUES('"+bid+"','"+uid+"','"+title+"','"+text+"','"+date+"');");
        	sql.close();
        	con.close();
        	response.sendRedirect("status.jsp");
  		}
  		catch(SQLException e1) { out.print(e1); }
	}
	%>
</body>

</html>