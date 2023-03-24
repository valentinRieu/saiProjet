#include "interaction.h"

void jouerBonhommes(){
	int i, j;
	
	for(i=0;i<NB_BONHOMMES;i++){
		j = lePlusProche(i, 0);//id
		//fuir j
		if(j==-1){
			deplacerAlea(i, 0);
		}else{
			fuir(i, j);
		}
	}
}

void jouerAnimaux(){
	int i, j;
	
	for(i=0;i<NB_ANIMAUX;i++){
		j = lePlusProche(i, 1);//id
		//aller vers j
		if(j==-1){
			deplacerAlea(i, 1);
		}else{
			attraper(i, j);
		}
	}
}

//théorème de pythagore pour les surfaces
int py(int x, int y){
    return x*x+y*y;
}

int lePlusProche(int id, int type){
	int i, min, idMin=0;
	int x, y, d;
	point p, p2;
	
	if(type==0){
		p = bonhommes[id].pos;
		min=py(p.x-animaux[0].pos.x, p.y-animaux[0].pos.y);
		for(i=1;i<NB_ANIMAUX;i++){
			p2 = animaux[id].pos;
			if((d=py(p.x-p2.x, p.y-p2.y))<min){
				min = d;
				id = i;
			}
		}
	}else{
		p = animaux[id].pos;
		min=py(p.x-bonhommes[0].pos.x, p.y-bonhommes[0].pos.y);
		for(i=1;i<NB_BONHOMMES;i++){
			p2 = bonhommes[id].pos;
			if((d=py(p.x-p2.x, p.y-p2.y))<min){
				min = d;
				id = i;
			}
		}
	}
	if(min>60)
		return -1;
	return id;
}

int estAutorise(int id, int x, int y){
	return 1;
}

void deplacer(int id, int type){
	int i, j;
	
	if(type == 0){//verif cible
		i = bonhommes[id].pos.x+bonhommes[id].direction.x;
		j = bonhommes[id].pos.y+bonhommes[id].direction.y;
		if(estAutorise(id,i,j)){
			bonhommes[id].pos.x = i;
			bonhommes[id].pos.y = j;
		}else{
			bonhommes[id].isDepl = 0;
		}
	}else{
		i = animaux[id].pos.x+animaux[id].direction.x;
		j = animaux[id].pos.y+animaux[id].direction.y;
		if(estAutorise(id,i,j)){
			animaux[id].pos.x = i;
			animaux[id].pos.y = j;
		}else{
			animaux[id].isDepl = 0;
		}
	}
}

void modifierDirection(int id, int type){
	int x = rand()%1000;
	int y = rand()%1000;
	int dx, dy, k;
	
	if(type == 0){//modif direction
		k = sqrt(py(x-bonhommes[id].pos.x,y-bonhommes[id].pos.y))/10;
		dx = bonhommes[id].pos.x+k*(x-bonhommes[id].pos.x);
		dy = bonhommes[id].pos.y+k*(y-bonhommes[id].pos.y);
		bonhommes[id].direction.x = dx;
		bonhommes[id].direction.y = dy;
		bonhommes[id].cible.x = x;
		bonhommes[id].cible.y = y;
		bonhommes[id].isDepl = 1;
	}else{
		k = sqrt(py(x-animaux[id].pos.x,y-animaux[id].pos.y))/10;
		dx = animaux[id].pos.x+k*(x-animaux[id].pos.x);
		dy = animaux[id].pos.y+k*(y-animaux[id].pos.y);
		animaux[id].direction.x = dx;
		animaux[id].direction.y = dy;
		animaux[id].cible.x = x;
		animaux[id].cible.y = y;
		animaux[id].isDepl = 1;
	}
}

void deplacerAlea(int id, int type){
	if(type == 0 && bonhommes[id].isDepl == 0){
		modifierDirection(id, type);
	}else if(animaux[id].isDepl == 0){
		modifierDirection(id, type);
	}
	deplacer(id, type);
}

void fuir(int id1, int id2){
	
}

void attraper(int id1, int id2){
	
}