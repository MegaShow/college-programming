<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>

<%!
	String[] _username = {"root", "user1", "user2"};
	int[] _userperm = {0, 1, 1};
	String[] _userpwd = {"pwd123", "123456", "666666"};
%>

<html>
<head>
<title>登录</title>
</head>

<body>
	<form method="post" >
		用户 <input type="text" value="" name="username" ><br>
		密码 <input type="password" value="" name="password" ><br>
		<input type="submit" value="提交" name="submit"><br>
	</form>
	<%
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		if(username != null && username != ""){
			for(int i = 0; i < _username.length; i++){
				if(username.equals(_username[i])){
					if(password.equals(_userpwd[i])){
						session.setAttribute("username", username);
						session.setAttribute("password", password);
						session.setAttribute("permission", _userperm[i]);
						out.println("ok!test");
						response.sendRedirect("homepage.jsp");
					}
					else{
						out.println("密码不正确<br>");
						break;
					}
				}
				else if(i + 1 == _username.length){
					out.println("用户名不正确<br>");
				}
			}
		}
	%>
</body>

</html>
<!-- MegaShow -->