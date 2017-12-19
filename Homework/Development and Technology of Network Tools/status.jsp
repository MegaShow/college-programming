<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
    
<html>
<head>
	<title>MBlog|个人中心</title>
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
	%><div style="float:right">
		<a href="index.jsp"><input type="submit" name="index" value="主页"></a>
		<%=username%>的个人中心!
	</div><br><br><%
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
        	if (bid != null) {
        		sql.executeUpdate("DELETE FROM `mblog`.`blog` WHERE `bid`='"+ bid +"';");
        	}
        	rs = sql.executeQuery("select * from blog where uid="+uid+";");
        	out.print("<table border=2>");
        	out.print("<tr>");
        	out.print("<th width=100>" + "BlogID");
        	out.print("<th width=100>" + "作者");
        	out.print("<th width=150>" + "标题");
        	out.print("<th width=200>" + "正文");
        	out.print("<th width=180>" + "发布时间");
        	out.print("<th width=180>" + "修改时间");
        	out.print("<th width=50>");
        	out.print("<th width=50>");
        	out.print("</TR>");
        	while(rs.next()) {
            	out.print("<tr>");
            	out.print("<td>" + rs.getInt("bid") + "</td>"); 
            	out.print("<td>" + username + "</td>");
            	out.print("<td>" + rs.getString("title") + "</td>"); 
            	out.print("<td>" + rs.getString("text") + "</td>");
            	out.print("<td>" + rs.getString("time") + "</td>");
            	out.print("<td>" + rs.getString("modify_time") + "</td>");
            	%><td><form action="modify.jsp" method="post">
            				<input type="hidden" name="bid" value="<%=rs.getInt("bid")%>">
            				<input type="submit" name="submit" value="修改">
            	</form></td>
            	<td><form method="post">
					<input type="hidden" name="bid" value="<%=rs.getInt("bid")%>">
					<input type="submit" name="submit" value="删除">
				</form></td><%
            	out.print("</tr>") ; 
        	}
        	out.print("</table>");
        	sql.close();
        	con.close();
    	}
    	catch(SQLException e1) { out.print(e1); }
    	if (is_valid.equals("0")) {
    		%><br>
    		<form action="localhost/sendmail.html" method="get">
    			<input type="hidden" name="email" value="<%=email%>">
    			<input type="hidden" name="title" value="<%=username%>,MBLOG邮箱认证!">
    			<input type="hidden" name="content" value="认证邮箱请点击下面链接:http://172.18.34.3:8080/JSP/confirm.jsp?token=<%=username%>">
    			<input type="submit" name="confirm" value="发送认证邮件">
    		</form>
    		<%
    		out.println("请及时认证您的邮箱!");
    	}
	}
	%>
</body>

</html>
