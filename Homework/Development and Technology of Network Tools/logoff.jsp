<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
    
<html>
<head>
	<title>MBlog|退出</title>
</head>

<body>
	<%
	session.invalidate();
	response.sendRedirect("index.jsp");
	%>
</body>

</html>