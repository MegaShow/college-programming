<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ taglib tagdir="/WEB-INF/tags" prefix="area"%>

<html>

<head>
<title>TAG</title>
</head>

<body>
	<form method="post" >
		<input type="text" value="请输入矩形的长" name="width" ><br>
		<input type="text" value="请输入矩形的宽" name="height" ><br>
		<input type="text" value="请输入圆的半径" name="r" ><br>
		<input type="submit" value="提交" name="submit" ><br>
	</form>
	<%
		String szWidth = request.getParameter("width");
		String szHeight = request.getParameter("height");
		String szR = request.getParameter("r");
		boolean rectFlag = true;
		boolean circleFlag = true;
		if(szWidth != null && szHeight != null){
			%><area:Rect width="<%= szWidth %>" height="<%= szHeight %>" /><%
		}
		if(szR != null){
			%><area:Circle ri="<%= szR %>" /><%
		}
	%>
</body>

</html>
<!-- MegaShow -->