void charupaixu1(int *nums, int numsSize) 
{
	for (int i = 1; i < numsSize; i++) 
        {
		int key = nums[i];//把要插入的值先提取出来

		int j = i - 1;
		while (j >= 0 && nums[j] > key) //当前面已排序的数比待排序的数大时，已排序的数往后挪一位，给待插入的数腾出位置,这样会把key原来的位置占了，但我们已经把key提取出来了，所以没关系
                {
			nums[j + 1] = nums[j];
			j--;
		}
		nums[j + 1] = key;
                //这里用j+1的原因是：当前面的while循环把比key大的书往后挪后，j进行自减，导致j代表的数从空位到了空位后一格，若发现条件不成立(即发现key比前面的数大，比后面的数小)，结束循环，此时j指的是空位前一位，所以要加一
	}

}
