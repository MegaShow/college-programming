<!doctype html>

<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>

<%!

boolean isValidChar(char c){
    return (('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9') || c=='-' || c=='_');
}

boolean isValidEmail(String email){
    int atIndex = email.indexOf("@");
    if(atIndex == -1 || atIndex + 1 == email.length())
        return false;
    for(int i = 0; i < atIndex; i++){
        char c = email.charAt(i);
        if(!isValidChar(c))
            return false;
    }
    boolean domain = false, domain2 = false;
    for(int i = atIndex + 1; i < email.length(); i++){
        char c = email.charAt(i);
        if(isValidChar(c))
            domain = true;
        else if(c == '.' && domain){
            domain = false;
            domain2 = true;
        }
        else
            return false;
    }
    return (domain && domain2);
}

boolean isValidUsername(String username){
    return username.length() > 0 && username.length() <= 15;
}

boolean isValidPassword(String password){
    if(password.length() < 6 || password.length() > 20)
        return false;
    for(int i = 0; i < password.length(); i++){
        if(password.charAt(i) == ' ')
            return false;
    }
    return true;
}

boolean isValidPasswordAgain(String password, String password_again) {
	return password.equals(password_again);
}

%>


<html>
<head>
	<title>MBlog|注册</title>
</head>

<body style="text-align:center">
	<form method="post">
		<input type="email" name="email" value="">邮箱&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
		<input type="text" name="username" value="">用户名&nbsp;&nbsp;&nbsp;&nbsp;<br>
		<input type="password" style="width:148px" name="password" value="">密码&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
		<input type="password" style="width:148px" name="password-again" value="">确认密码<br>
		<input type="submit" name="submit" value="注册"><br>
	</form>
	Tips:用户名(15字内) | 密码(6-20字符,不包含空格)<br>
	<%
    request.setCharacterEncoding("utf-8");
    String email = request.getParameter("email");
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    String password_again = request.getParameter("password-again");
    if (email!=null || username!=null || password!=null || password_again!=null) {
    	boolean validEmail = isValidEmail(email);
        boolean validUsername = isValidUsername(username);
        boolean validPassword = isValidPassword(password);
        boolean validPasswordAgain = isValidPasswordAgain(password, password_again);
        if(!validEmail)
            %><p>邮箱不合法</p><%
        if(!validUsername)
            %><p>用户名不合法</p><%
        if(!validPassword)
            %><p>密码不合法</p><%
        if(!validPasswordAgain)
        	%><p>两次密码输入不一致</p><%
        if(validEmail && validUsername && validPassword && validPasswordAgain) {
        	// 写入数据库
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
           		rs = sql.executeQuery("SELECT * FROM user where email='" + email + "';");
           		if (rs.next()) {
           			out.println("该邮箱已注册!");
           		} else {
           			rs = sql.executeQuery("select * from globe where id=1");
           			rs.next();
           			uid = rs.getInt("value") + 1;
           			sql.executeUpdate("UPDATE `mblog`.`globe` SET `value`='"+uid+"' WHERE `id`='1';");
            		sql.executeUpdate("INSERT INTO `mblog`.`user`(`uid`,`email`,`name`,`password`,`is_valid`)VALUES('"+uid+"','"+email+"','"+username+"','"+password+"','0');");
            		sql.close();
            		con.close();
            		session.setAttribute("uid", Integer.toString(uid));
                	session.setAttribute("email", email);
                	session.setAttribute("username", username);
                	session.setAttribute("is_valid", "0");
                	response.sendRedirect("index.jsp");
           		}
      		}
      		catch(SQLException e1) { out.print(e1); }
        }
    }
    %>
</body>

</html>

