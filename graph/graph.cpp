int di[4]={-1,0,1,0};
int dj[4]={0,1,0,-1};

const int dirx[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
const int diry[] = { 1, -1, 0, 0, -1, 1, 1, -1 };

bool canMove(int i, int j){
    return i>-1 && i<n && j>-1 && j<2;
}


