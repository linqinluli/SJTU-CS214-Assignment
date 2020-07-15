/*********************************************
 * OPL 12.9.0.0 Model
 * Author: yhz
 * Creation Date: 2020年4月11日 at 上午9:38:26
 *********************************************/
{string} Products= ...;
{string} Machine= ...;

float Consumption[Machine][Products]=...;
float profit[Products]=...;
float limitation[1..6][Products]=...;
int Machinenum[Machine]=...;
dvar int+ monthhold[Products][0..6];
dvar int+ monthmake[Products][1..6];
dvar int+ maintenance[Machine][1..6];
dvar int+ monthsell[Products][1..6];
dvar float totalsell;
dvar float totalholdcost;


maximize
  sum(x in Products, i in 1..6)
    (monthsell[x][i]*profit[x]-monthhold[x][i]*0.5);
   
subject to{
forall(p in Products, i in 1..6)
  ctselllimitation:
    monthsell[p][i]<=limitation[i][p];
  
forall(m in Machine, i in 1..6)
  ctmonthmake:
  	sum(p in Products)
  		(Consumption[m][p]*monthmake[p][i]) <= (Machinenum[m]-maintenance[m][i])*384;
  		
forall(m in Machine)
  ctmaintenance:
  	sum(i in 1..6)
  	  (maintenance[m][i])==Machinenum[m];

forall(p in Products)
  ctzero:
  	monthhold[p][0]==0;
 
forall(p in Products, i in 1..6)
  ctholdlimitation:
  	{  	
  	monthmake[p][i]-monthsell[p][i]+monthhold[p][i-1]<=100;
  	monthhold[p][i]==monthmake[p][i]-monthsell[p][i]+monthhold[p][i-1];
  	monthhold[p][6]==50;
  	}
 totalsell==sum(x in Products, i in 1..6)
    (monthsell[x][i]*profit[x]);
    
 totalholdcost==sum(x in Products, i in 1..6)
 (monthhold[x][i]*0.5);

   	

}