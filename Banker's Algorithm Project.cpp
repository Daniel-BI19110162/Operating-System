#include <stdio.h>

bool safety(int available[], int allocation[][3], int need[][3], int claim[][3], int number_process, int work[], int temp_alloc[][3], int temp_need[][3]){
    int safe_sequence[5] = {0,0,0,0,0};
    int finish[5] = {0, 0, 0, 0, 0};
    int index = 0;
	for(int out = 0; out < 5; out++){
		
		for(int j = 0; j < 5; j++){
			if(finish[j] == 0){
				//int process = j;
				int flag = 0; // this flag is to determine wether need is larger than work
				for(int k = 0; k < 3; k++){
					if(temp_need[j][k] <= work[k]){
						flag = 0;
					}
					else{
						flag = 1;
						break;
					}
				}
				if(flag == 0){
					safe_sequence[index++] = j;
					printf("\n\nProcess %d is executing.", j);
					printf("\nAvailable vector: ");
					for(int y = 0; y < 3; y++){
						work[y] += temp_alloc[j][y];
						printf("%d ", work[y]);
					}
					finish[j] = 1;
				}
			}
		}
	}
	for(int i = 0; i < 5; i++){
		if(finish[i] == 0){
			printf("\n\nThe process is not in a safe state\n");
			for(int j = 0; j < 5; j++){
				if(finish[j] == 0)
					printf("\nTrapped process %d", j);
			}
			return false;
		}
		if(i == 4){
			printf("\n\nThe process is in a safe state");
			printf("\n\nThe safe sequence are: ");
			for(int j = 0; j < 4; j++){
				printf("P%d -> ", safe_sequence[j]);
			}
			printf("P%d", safe_sequence[4]);
			return true;
		}
	}
}

bool resource_request(int available[], int max[][3], int allocation[][3], int need[][3], int claim[][3], int total_allocation[], int number_process)
{
    bool safe = false;
    int flag = 0;
    int work[3];
    int temp_alloc[5][3];
    int temp_need[5][3];
    int temp_total_allocation[3];
    ///assign temp available
    for(int i = 0; i < 5; i++){
			work[i] = available[i]; 
	}
	 //assign temp need
    for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			temp_need[i][j] = need[i][j]; 
		}
	}
	 //assign temp allocation
    for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			temp_alloc[i][j] = allocation[i][j]; 
		}
	}
	 //assign temp total_allocation
	for(int j = 0; j < 3; j++){
		temp_total_allocation[j] = total_allocation[j]; 
	}
	
    for(int j = 0 ; j < 3;j++) {
        if(claim[number_process][j] > need[number_process][j]) {
            printf("Error occured\n");
            flag = 1;
        }
        if(claim[number_process][j] > available[j])
        {
            printf("Not available\n");
      		flag = 1; 
        }
	}
	
	if(flag == 0){
		for(int j = 0 ; j < 3;j++)
        {
            work[j] -= claim[number_process][j];
            temp_total_allocation[j] += claim[number_process][j];
            temp_alloc[number_process][j] += claim[number_process][j];
            temp_need[number_process][j] -= claim[number_process][j];
        }
       	printf("\nRemaining Need Table After claim:\n");//print allocation table
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 3; j++){
				printf("%d\t", temp_need[i][j]);
			}
		printf("\n");}
		
		printf("\n\nThe Allocated Resource Table After claim:\n");//print allocation table
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 3; j++){
				printf("%d\t", temp_alloc[i][j]);
			}	
		printf("\n");}
		
		printf("\nThe Maximum Claim Table:\n");//print allocation table
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 3; j++){
				printf("%d\t", max[i][j]);
			}
		printf("\n");}
		
		printf("\n\nAllocated resources After claim:");//print total allocated resouces
		for(int i = 0; i < 3; i++){
				printf("%d ", temp_total_allocation[i]);
		}
		
		printf("\nAvailable Resources:");//print available resources
		for(int i = 0; i < 3; i++){
			printf("%d ", work[i]);
		}
		
		safe = safety(available,allocation,need,claim,number_process, work, temp_alloc, temp_need);
	}
	if(safe == true){
		for(int j = 0 ; j<3;j++)
        {
            available[j] = available[j] - claim[number_process][j];
            total_allocation[j] = total_allocation[j] + claim[number_process][j];
            allocation[number_process][j] = allocation[number_process][j] + claim[number_process][j];
            need[number_process][j] = need[number_process][j] - claim[number_process][j];
        }	
	}
    return safe;
}

void input_claim(int claim[][3], int number_process) {// input for process claim resource
	for(int i=0;i<3;i++){
        scanf("%d",&claim[number_process][i]);
    }
}

int main() {
	// P0, P1, P2, P3, P4 are the Process names here
	int number_process = 0;
	int claim[5][3];
    int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
                        { 3, 0, 2 }, // P1
                        { 3, 0, 2 }, // P2
                        { 2, 1, 1 }, // P3
                        { 0, 0, 2 } }; // P4
  
    int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
                      { 3, 2, 2 }, // P1
                      { 9, 0, 2 }, // P2
                      { 2, 2, 2 }, // P3
                      { 4, 3, 3 } }; // P4
	int tot_avail[3] = {10, 5, 7}; //Total of available resource
    int avail[3] = {2, 3, 0}; // Available Resources
    int tot_alloc[3] = {0, 0, 0}; // store total allocate resources
    bool loop_out = true;
    
    int need[5][3];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    
    printf("The Total Claimaible Resources are:");//print total Avaialble
    for(int i = 0; i < 3; i++){
    	printf("%d ", tot_avail[i]);
	}
	printf("\n\nThe Allocated Resource Table:\n");//print allocation table
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			printf("%d\t", alloc[i][j]);
		}
		printf("\n");
	}
	printf("\nThe Maximum Claim Table:\n");//print allocation table
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			printf("%d\t", max[i][j]);
		}
		printf("\n");
	}
	printf("\nThe Process Need Table:\n");//print allocation table
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			printf("%d\t", need[i][j]);
		}
		printf("\n");
	}
	//sum all the allocated resources
	int next = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 1; k++)
				tot_alloc[i] += alloc[j][next];
		}
		next++;
	}
	next = 0;// the use to add one element from the alloc array
	
	printf("\n\nAllocated Resources:");//print total allocated resouces
	for(int i = 0; i < 3; i++){
		printf("%d ", tot_alloc[i]);
	}
	printf("\nAvailable Resources:");//print available resources
	for(int i = 0; i < 3; i++){
		printf("%d ", avail[i]);
	}
    while(loop_out){
    	printf("\n\nResource claim:");
    	printf("\nWhich process need request? ");
    	scanf("%d", &number_process);
 		printf("\nProcess %d wants to claim: ",number_process);
		input_claim(claim, number_process);
    	loop_out = resource_request(avail, max, alloc, need, claim, tot_alloc, number_process);// wiil loop out if false (process is not in safe state)
    }
    return 0;
}
