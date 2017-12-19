<%@ tag pageEncoding="UTF-8" %>

<%@ attribute name="ri" required="true" %>

<%!
double getCircleArea(double r){
	return Math.PI * r * r;
}
%>

<%
try{
	double r = Double.parseDouble(ri);
	if(r > 0)
		out.println("半径:"+r+" 面积:"+getCircleArea(r)+"<br>");
	else
		out.println("半径非正，不合法！<br>");
}
catch(NumberFormatException e){
	out.println("请输入正确的圆的半径！<br>");
}
%>
<!-- MegaShow -->