<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
    
<html>
<head>
	<title>MBlog|登录</title>
</head>

<body style="text-align:center">
	<form method="post">
		<input type="email" name="email" value="">邮箱<br>
		<input type="password" style="width:148px" name="password" value="">密码<br>
		<input type="submit" name="submit" value="登录"><br>
	</form>
	<%
	request.setCharacterEncoding("utf-8");
	String email = request.getParameter("email");
	String password = request.getParameter("password");
	if (email != null) {
		Connection con;
  		Statement sql; 
  		ResultSet rs;
  		int uid = 0;
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
       		rs = sql.executeQuery("select * from user where email='"+email+"';");
       		if(rs.next()) {
	       		if (password.equals(rs.getString("password"))) {
    	      		session.setAttribute("uid", Integer.toString(rs.getInt("uid")));
        	    	session.setAttribute("email", email);
            		session.setAttribute("username", rs.getString("name"));
            		session.setAttribute("is_valid", Integer.toString(rs.getInt("is_valid")));
            		response.sendRedirect("index.jsp");
       			} else {
       				out.println("密码错误!");
       			}
       		} else {
       			out.println("查无此邮箱注册用户!");
       		}
       		sql.close();
       		con.close();
  		}
  		catch(SQLException e1) { out.print(e1); }
	}
	%>
</body>

</html>