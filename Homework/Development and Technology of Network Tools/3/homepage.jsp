<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>

<html>
<head>
<title>首页</title>
</head>

<body>
	<%
		String username = (String)session.getAttribute("username");
		String password = (String)session.getAttribute("password");
		int permission = (int)session.getAttribute("permission");
		out.println(username + ", 欢迎您！<br>");
		out.println("您的用户权限是:" + permission + " (0最高1最低)");
	%>
</body>

</html>
<!-- MegaShow -->