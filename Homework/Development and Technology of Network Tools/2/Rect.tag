<%@ tag pageEncoding="UTF-8" %>

<%@ attribute name="width" required="true" %>
<%@ attribute name="height" required="true" %>

<%!
double getRectArea(double width, double height){
	return width * height;
}
%>

<%
try{
	double w = Double.parseDouble(width);
	double h = Double.parseDouble(height);
	if(w > 0 && h > 0)
		out.println("长:"+w+" 宽:"+h+" 面积:"+getRectArea(w, h)+"<br>");
	else
		out.println("矩形长宽不合法！<br>");
}
catch(NumberFormatException e){
	out.println("请输入正确的矩形的长宽！<br>");
}
%>
<!-- MegaShow -->