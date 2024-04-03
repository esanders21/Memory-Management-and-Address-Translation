# Memory-Management-and-Address-Translation
## getPhysicalAdd
input the number of pages as num_page, frame size as fram_size, page number as page_num_calc, the offset as offset, and the logical address as l_adress. It then chacks to make sure the page number is less than th number of pages. after definePageTable is used to get the frame numnber. Then using the equation frameNumber * frame_size + offset you get the physical address. then check to make sure that the logcal address and physical address are not equal. Lastly page number is compared to the table values and the results are displayed. 

## definePageTable
Initializes page/frame table, allocates frames in physical memory, fill page/frame table and physical memory.

## main()
in main I get logical address from on line 65 with logicalAddress.  Then (logicalAddress >> 8) & 0xFF is used to calculate the page number from the logical address and logicalAddress & 0xFF to calculate the offset. 
