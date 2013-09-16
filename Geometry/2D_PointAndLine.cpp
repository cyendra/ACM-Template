int dcmp(double x){
    if (fabs(x)<EPS) return 0;
    return x>0?1:-1;
}
struct point{
    double x,y;
    point(){}
    point(double _x,double _y):x(_x),y(_y){}
    /**运算操作**/
    bool operator==(point a)const{
        return dcmp(a.x-x)==0&&dcmp(a.y-y)==0;
    }
    bool operator<(point a)const{
        return dcmp(x-a.x)==0?dcmp(y-a.y)<0:dcmp(x-a.x)<0;
    }
    friend point operator+(point a,point b){
        return point(a.x+b.x,a.y+b.y);
    }//向量+向量=向量
    friend point operator-(point a,point b){
        return point(a.x-b.x,a.y-b.y);
    }//点-点=向量
    friend point operator*(point a,double p){
        return point(a.x*p,a.y*p);
    }//向量*数=向量
    friend point operator/(point a,double p){
        return point(a.x/p,a.y/p);
    }//向量/数=向量
    /**基本信息计算**/
    double len(){
        return hypot(x,y);
    }
    double len2(){
        return x*x+y*y;
    }
    double distance(point p){
        return hypot(x-p.x,y-p.y);
    }
    /**向量变换**/
    point rotate(double rad){
        return point(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
    }//绕起点逆时针旋转rad
    point rotate(point p,double angle)//绕点p逆时针旋转angle角度
    {
        point v=(*this)-p;
        double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
    point rotleft(){
        return point(-y,x);
    }//逆时针转90度
    point rotright(){
        return point(y,-x);
    }//顺时针转90度
    point normal(){
        double L=len();
        return point(-y/L,x/L);
    }//单位法线即左转90度长度归一
    point trunc(double r){
        double l=len();
        if (!dcmp(l)) return *this;
        r/=l;
        return point(x*r,y*r);
    }//长度变为r
    /**读入与输出**/
    void input(){
        scanf("%lf%lf",&x,&y);
    }
    void output(){
        printf("%0.2f %0.2f\n",x,y);
    }
};
typedef point vect;
double dot(point a,point b){
    return a.x*b.x+a.y*b.y;
}
double cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
double area3p(point a,point b,point c){
    return cross(b-a,c-a)/2;
}//三角形abc的面积
double angle(vect a,vect b){
    return acos(dot(a,b)/a.len()/b.len());
}
point GetLineIntersection(point P,vect v,point Q,vect w){
    vect u=P-Q;
    double t=cross(w,u)/cross(v,w);
    return P+v*t;
}//直线交点
double ConvexPolygonArea(point *p,int n){
    double area=0;
    for (int i=1;i<n-1;i++) area+=cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}//多边形面积

struct line{
    point a,b;
    line(){}
    line(point _a,point _b){a=_a;b=_b;}
    line(point p,double angle){
        a=p;
        if (dcmp(angle-PI/2)==0) b=a+point(0,1);
        else b=a+point(1,tan(angle));
    }//倾斜角angle
    line (double _a,double _b,double _c){
        if (dcmp(_a)==0){
            a=point(0,-_c/_b);
            b=point(1,-_c/_b);
        }else if (dcmp(_b)==0){
            a=point(-_c/_a,0);
            b=point(-_c/_a,1);
        }else{
            a=point(0,-_c/_b);
            b=point(1,(-_c-_a)/_b);
        }
    }//ax+by+c=0
    void adjust(){
        if (b<a) swap(a,b);
    }//两点校准
    /**运算操作**/
    bool operator==(line v){
        return (a==v.a)&&(b==v.b);
    }
    /**基本信息计算**/
    double length(){
        return a.distance(b);
    }
    double angle(){
        double k=atan2(b.y-a.y,b.x-a.x);
        if (dcmp(k)<0) k+=PI;
        if (dcmp(k-PI)==0) k-=PI;
        return k;
    }
    /**线段相关**/
    int relation(point p){
        int c=dcmp(cross(p-a,b-a));
        if (c<0) return 1;//点在逆时针
        if (c>0) return 2;//点在顺时针
        return 3;//平行
    }
    bool pointonseg(point p){
        return dcmp(cross(p-a,b-a))==0&&dcmp(cross(p-a,p-b))<=0;
    }//点p在线段上？
    bool parallel(line v){
        return dcmp(cross(b-a,v.b-v.a))==0;
    }//与线段v平行？
    int segcrossseg(line v){
        int d1=dcmp(cross(b-a,v.a-a));
        int d2=dcmp(cross(b-a,v.b-a));
        int d3=dcmp(cross(v.b-v.a,a-v.a));
        int d4=dcmp(cross(v.b-v.a,b-v.a));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
        return ((d1==0&&dcmp(dot(v.a-a,v.a-b)<=0))||
                (d2==0&&dcmp(dot(v.b-a,v.b-b)<=0))||
                (d3==0&&dcmp(dot(a-v.a,a-v.b)<=0))||
                (d4==0&&dcmp(dot(b-v.a,b-v.b)<=0)));
    }//线段相交 0-不相交 1-非规范相交 2-规范相交
    /**直线相关**/
    int linecrosseg(line v){//直线v
        int d1=dcmp(cross(b-a,v.a-a));
        int d2=dcmp(cross(b-a,v.b-a));
        if ((d1^d2)==-2) return 2;
        return (d1==0||d2==0);
    }//0-平行 1-重合 2-相交
    int linecrossline(line v){
        if ((*this).parallel(v)) return v.relation(a)==3;
        return 2;
    }//0-平行 1-重合 2-相交
    point crosspoint(line v){
        double a1=cross(v.b-v.a,a-v.a);
        double a2=cross(v.b-v.a,b-v.a);
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }//交点
    double dispointtoline(point p){
        return fabs(cross(p-a,b-a))/length();
    }//点到线的距离
    double dispointtoseg(point p){
        if (dcmp(cross(p-b,a-b))<0||dcmp(cross(p-a,b-a))<0) return min(p.distance(a),p.distance(b));
        return dispointtoline(p);
    }
    /**输入输出**/
    void input(){
        a.input();
        b.input();
    }
    void output(){
        a.output();
        b.output();
    }
};
