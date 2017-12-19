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
	String bid = request.getParameter("bid");
	String new_title = request.getParameter("title");
	String new_text = request.getParameter("text");
	if (uid == null) {
		out.println("请先登录后操作!");
		%>
		<form action="login.jsp" method="post">
			<input type="submit" name="submit" value="登录">
		</form>
		<%
	} else if (new_title == null && bid == null) {
		out.println("请求非法!");
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
   			if (new_title == null) {
   				rs = sql.executeQuery("select * from blog where bid=" + bid);
   				rs.next();
   				String title = rs.getString("title");
   				String text = rs.getString("text");
   				%><form method="post">
   					<input type="hidden" name="bid" value="<%=bid%>">
					<input type="text" name="title" value="<%=title%>"><br>
					<textarea name="text" cols="30" rows="5"><%=text%></textarea><br>
					<input type="submit" name="submit" value="修改Blog"><br>
				</form><%
   			} else {
   				java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
   		   		java.util.Date currentTime = new java.util.Date();//得到当前系统时间
   		   		String date = formatter.format(currentTime); //将日期时间格式化 
   		   		sql.executeUpdate("UPDATE `mblog`.`blog` SET `title`='"+new_title+"', `text`='"+new_text+"', `modify_time`='"+date+"' WHERE `bid`='"+bid+"';");
   		   		response.sendRedirect("status.jsp");
   			}
   			sql.close();
    		con.close();
		}
		catch(SQLException e1) { out.print(e1); }
	}
	%>
</body>

</html>