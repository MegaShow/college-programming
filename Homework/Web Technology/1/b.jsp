<!doctype html>
<%@ page contentType="text/html;charset=utf-8" %>

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

%>


<html>

<body>
    <%
        request.setCharacterEncoding("utf-8");
        String email = request.getParameter("email");
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean validEmail = isValidEmail(email);
        boolean validUsername = isValidUsername(username);
        boolean validPassword = isValidPassword(password);
    %>

    <%
        if(!validEmail)
            %><p>邮箱不合法</p><%
        if(!validUsername)
            %><p>用户名不合法</p><%
        if(!validPassword)
            %><p>密码不合法</p><%
        if(validEmail && validUsername && validPassword)
            %><p>注册成功</p><title>注册成功</title><%
        else
            %><title>注册失败</title><%
    %>

    <p>邮箱：<%= email %></p>
    <p>用户名：<%= username %></p>
    <p>密码:<%= password %></p>
    <button onclick="javascript:window.location.href='a.jsp'">返回</button>
</body>


</html>
<!-- MegaShow 2017 -->