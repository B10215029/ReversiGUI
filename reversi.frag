#version 430 core
//fragment shader
//uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;
uniform int[64] data;
out vec4 fragmentcolor; 

bool circular(float x, float y){
	float nx=abs(abs(x)-0.25);
	float ny=abs(abs(y)-0.25);
	float d=sqrt(nx*nx+ny*ny);
	return (d<0.25 && d>0.188);
}

bool number(float x, float y, int num){
	float nx=x*1.2;
	float ny=(y+(y<0?0.5:0.))*1.2;
	if(num == 0){
		if(abs(nx)>0.25)
			return circular(nx, ny);
		else
			return (abs(ny-0.25)<0.25 && abs(ny-0.25)>0.188);
	}
	else if(num == 1){
		if(abs(nx)<0.5){
			if(abs(ny-0.25)<0.031)
				return true;
			if(nx<0.5 && nx > 0.438 && ny<0.5)
				return true;
			if(nx<-0.25 && ny<0.25)
				return (abs(-nx-0.25-ny)<0.0438);
		}
	}
	else if(num == 2){
		if(nx < -0.25)
			return circular(nx, ny);
		if(nx > -0.25 && nx < 0.5 && ny > 0 && ny < 0.5)
			if(abs((nx - 0.5) * 2 + ny * 3 ) < 0.11)
				return true;
		if(ny > 0 && ny < 0.5)
			if(nx < 0.5 && nx > 0.4388)
				return true;
	}
	else if(num == 3){
		if(abs(nx)>0.25 || ny > 0.25)
			return circular(nx, ny);
	}
	else if(num == 4){
		if(nx > -0.5 && nx < 0.5 && ny > 0 && ny < 0.5){
			if(abs(nx) < 0.031 || abs(ny - 0.25) < 0.031)
				return true;
			if(nx < 0 && ny < 0.062)
			//if(nx < 0 && abs(ny * 2 + nx) < 0.0554)
				return true;
		}
	}
	else if(num == 5){
		if(nx > 0 && (nx > 0.25 || ny > 0.25))
			return circular(nx, ny);
		if(nx > -0.5 && nx < 0.5 && ny > 0 && ny < 0.5)
			if(nx < -0.4388 || (ny < 0.062 && nx < 0) || (nx > 0 && nx < 0.062))
				return true;
	}
	else if(num == 6){
		if(nx > 0 || nx < -0.25)
			if(circular(nx, ny))
				return true;
		if(abs(nx) < 0.25 && ny < 0.062)
			return true;
	}
	else if(num == 7){
		if(nx > -0.5 && nx < 0.5 && ny > 0 && ny < 0.5){
			if(nx < -0.4388)
				return true;
			if(abs(nx + (ny - 0.25) * 2) < 0.0554)
				return true;
		}
	}
	else if(num == 8){
		return circular(nx, ny);
	}
	else if(num == 9){
		if(nx < 0 || nx > 0.25)
			if(circular(nx, ny))
				return true;
		if(abs(nx) < 0.25 && ny > 0.4388 && ny < 0.5)
			return true;
	}
	return false;
}

void main(){
	float x = (1-gl_FragCoord.y/resolution.y)*1.125;
	float y = gl_FragCoord.x/resolution.x;
	int index = int(x*8) + int(y*8)*8;
	float xx = (x*8-int(x*8))-0.5;
	float yy = (y*8-int(y*8))-0.5;
	float dist = (xx*xx+yy*yy)*4;
	if(abs(xx) > 0.475 || (abs(yy) > 0.475 && x < 1)){//格線
		fragmentcolor = vec4(0.0, 0.0, 0.0, 1.0);
		return;
	}
	if(x < 1 && dist < 0.8 && data[index] != 0){//棋子
		if(data[index] == 1)
			fragmentcolor = vec4(0.5-dist*0.5, 0.5-dist*0.5, 0.5-dist*0.5, 1.0);
		else
			fragmentcolor = vec4(1-dist*dist, 1-dist*dist, 1-dist*dist, 1.0);
		return;
	}
	if(x > 1){//狀態列
		if(int(y*8)==0 && dist < 0.8){
			fragmentcolor = vec4(0.5-dist*0.5, 0.5-dist*0.5, 0.5-dist*0.5, 1.0);
			return;
		}
		if(int(y*8)==2 && dist < 0.8){
			fragmentcolor = vec4(1-dist*dist, 1-dist*dist, 1-dist*dist, 1.0);
			return;
		}
		if(int(y*8)==1){
			int sum=0;
			for(int i=0;i<64;++i)
				sum+=data[i]==1?1:0;
			if((yy<0 && number(xx, yy, sum/10)) || (yy>0 && number(xx, yy, sum%10))){
				fragmentcolor = vec4(0,0,0,1);
				return;
			}
		}
		if(int(y*8)==3){
			int sum=0;
			for(int i=0;i<64;++i)
				sum+=data[i]==2?1:0;
			if((yy<0 && number(xx, yy, sum/10)) || (yy>0 && number(xx, yy, sum%10))){
				fragmentcolor = vec4(0,0,0,1);
				return;
			}
		}
		if(int(y*8)==7 && dist < 0.8){
			int sum=0;
			for(int i=0;i<64;++i)
				sum+=data[i]!=0?1:0;
			if(sum%2 == 0)
				fragmentcolor = vec4(0.5-dist*0.5, 0.5-dist*0.5, 0.5-dist*0.5, 1.0);
			else
				fragmentcolor = vec4(1-dist*dist, 1-dist*dist, 1-dist*dist, 1.0);
			return;
		}
	}
	//底色
	fragmentcolor = vec4(242/255., 196/255., 119/255., 1.0);
}
