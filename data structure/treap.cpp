void split(node *now,int x,node* &a,node* &b){
	//split first x nodes
	if(now==nil){a=b=nil;return;}
	now->push();
	if(now->L->size+1 <= x){
		a=now;
		split(now->R,x-now->L->size-1,a->R,b);
		a->pull();
	}
	else{
		b=now;
		split(now->L,x,a,b->L); 
		b->pull();
	}
}
node* merge(node *a,node *b){
	if(a==nil)return b;
	else if(b==nil)return a;
	if( b->hval <= a->hval){
		a->push();
		a->R = merge(a->R,b);
		a->pull();
		return a;
	}
	else{
		b->push();
		b->L = merge(a,b->L);
		b->pull();
		return b;
	}
}
