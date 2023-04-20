#include "interaction.h"

int estEnVie(int id, int type){
	if(id == -1){//joueur
		return joueur.enVie;
	}else if(type == 0){//bonhomme
		return bonhommes[id].enVie;
	}else{//animal
		return animaux[id].enVie;
	}
}

void jouerBonhommes(){
	int i, j;
	
	for(i=0;i<NB_BONHOMMES;i++){
		if(!estEnVie(bonhommes[i], 0))
			continue;
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
		if(!estEnVie(animaux[i]), 1)
			continue;
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
		min=py(p.x-joueur.pos.x, p.y-joueur.pos.y);
		for(i=0;i<NB_BONHOMMES;i++){
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

int estAutorise(int id, int x, int y, int type){
	if(id == -1){//joueur
		
	}else if(type == 0){//bonhomme
		
	}else{//animal
		
	}
	return 1;
}

void deplacer(int id, int type){
	int i, j;
	
	if(type == 0){
		i = bonhommes[id].pos.x+bonhommes[id].direction.x;
		j = bonhommes[id].pos.y+bonhommes[id].direction.y;
		if(estAutorise(id,i,j,0)){
			bonhommes[id].pos.x = i;
			bonhommes[id].pos.y = j;
		if(x-bonhommes[id].cible.x < 10 && x-bonhommes[id].cible.x > -10 && y-bonhommes[id].cible.y < 10 && y-bonhommes[id].cible.y > -10){
			bonhommes[id].isDepl = 0;
		}
		}else{
			bonhommes[id].isDepl = 0;
		}
	}else{
		i = animaux[id].pos.x+animaux[id].direction.x;
		j = animaux[id].pos.y+animaux[id].direction.y;
		if(estAutorise(id,i,j,1)){
			animaux[id].pos.x = i;
			animaux[id].pos.y = j;
			if(x-animaux[id].cible.x < 10 && x-animaux[id].cible.x > -10 && y-animaux[id].cible.y < 10 && y-animaux[id].cible.y > -10){
				animaux[id].isDepl = 0;
			}
		}
		}else{
			animaux[id].isDepl = 0;
		}
	}
}

void modifierDirection(int id, int type){
	int x = rand()%1000;
	int y = rand()%1000;
	int dx, dy, d;
	
	if(type == 0){//modif direction
		dx = x-bonhommes[id].pos.x;
		dy = y-bonhommes[id].pos.y;
		d = sqrt(py(dx, dy));
		/*k = sqrt(py(x-bonhommes[id].pos.x,y-bonhommes[id].pos.y))/10;
		dx = bonhommes[id].pos.x+k*(x-bonhommes[id].pos.x);
		dy = bonhommes[id].pos.y+k*(y-bonhommes[id].pos.y);*/
		bonhommes[id].direction.x = 10*(float(dx)/float(d));
		bonhommes[id].direction.y = 10*(float(dy)/float(d));
		bonhommes[id].cible.x = x;
		bonhommes[id].cible.y = y;
		bonhommes[id].isDepl = 1;
	}else{
		dx = x-bonhommes[id].pos.x;
		dy = y-bonhommes[id].pos.y;
		d = sqrt(py(dx, dy));
		/*k = sqrt(py(x-animaux[id].pos.x,y-animaux[id].pos.y))/10;
		dx = animaux[id].pos.x+k*(x-animaux[id].pos.x);
		dy = animaux[id].pos.y+k*(y-animaux[id].pos.y);*/
		animaux[id].direction.x = 10*(float(dx)/float(d));
		animaux[id].direction.y = 10*(float(dy)/float(d));
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
	int x, y, dx, dy, d;
	
	dx = bonhommes[id1].pos.x-animaux[id2].pos.x;
	dy = bonhommes[id1].pos.y-animaux[id2].pos.y;
	d = sqrt(py(dx, dy));
	x = bonhommes[id1].pos.x-10*(float(dx)/float(d));
	y = bonhommes[id1].pos.y-10*(float(dy)/float(d));
	if(estAutorise(id1, x, y, 0)){
		bonhommes[id1].pos.x = x;
		bonhommes[id1].pos.y = y;
	}
}

void attraper(int id1, int id2){
	int x, y, dx, dy, d;
	
	dx = animaux[id1].pos.x-bonhommes[id2].pos.x;
	dy = animaux[id1].pos.y-bonhommes[id2].pos.y;
	d = sqrt(py(dx, dy));
	x = animaux[id1].pos.x+10*(float(dx)/float(d));
	y = animaux[id1].pos.y+10*(float(dy)/float(d));
	//il faut vérifier ici si l'animal a attrapé le bonhomme
	if(estAutorise(id1, x, y, 1)){
		animaux[id1].pos.x = x;
		animaux[id1].pos.y = y;
	}
}