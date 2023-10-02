void selection(int *nums, int numsSize) 
{
	
  for (int i = 0; i < numsSize; i++) 
  {
		int minj = i;

		int min = INT_MAX;//记得调用<limits.h>

		for (int j = i; j < numsSize; j++) 
    {
			if (nums[j] < min) {
				min = nums[j];
				minj = j;
			}

		}
		if (minj != i) 
    {
			int tmp = nums[i];
			nums[i] = nums[minj];
			nums[minj] = tmp;
		}
	
  }

  
}


  
