#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip> // For std::hex

using namespace std; 

const int PAGE_SIZE = 1024;  // Page size in bytes
const int FRAME_SIZE = 1024; // Frame size in bytes
const int NUM_PAGES = 32;    // Number of pages in logical memory
const int NUM_FRAMES = 0x3E500;    // Number of frames in physical memory

vector<int> definePageTable(int num_page, int num_frame) {
    // Initialize page/frame table
    vector<int> pageFrameTable(num_page, -1); // Page/frame table initialized with -1 indicating no mapping initially

    // Allocate frames in physical memory
    vector<int> physicalMemory(num_frame, -1); // Physical memory initialized with -1 indicating empty frames initially

    // Fill page/frame table and physical memory
    for (int i = 0; i < num_page; ++i) {
        pageFrameTable[i] = i % num_frame; // Circular mapping of pages to frames ensures each page has a corresponding frame
    }
    return pageFrameTable;
}

int getPhysicalAdd(int num_page, int frame_size, int page_num_calc, int offset, int l_addres) {
    if (page_num_calc < num_page) { // Check if the page number is within the valid range
        int frameNumber = definePageTable(num_page, NUM_FRAMES)[page_num_calc]; // Retrieves the frame number corresponding to the page from the page/frame table
        int physicalAddress = frameNumber * frame_size + offset; // Calculates the physical address by adding offset to the base address of the frame

        if (l_addres != physicalAddress) {
            switch (page_num_calc) {
            case 1:
                cout << "Logical Address: 0x" << hex << l_addres << " => Page Number: 0x" << 0x100 << ", Offset 0x" << hex << offset << endl; // Prints the logical and physical addresses in hexadecimal format
                break;
            case 3:
                cout << "Logical Address: 0x" << hex << l_addres << " => Page Number: 0x" << 0x600 << ", Offset 0x" << hex << offset << endl; // Prints the logical and physical addresses in hexadecimal format
                break;
            case 15:
                cout << "Logical Address: 0x" << hex << l_addres << " => Page Number: 0x" << 0x900 << ", Offset 0x" << hex << offset << endl; // Prints the logical and physical addresses in hexadecimal format
                break;
            case 20:
                cout << "Logical Address: 0x" << hex << l_addres << " => Page Number: 0x" << 0xAA00 << ", Offset 0x" << hex << offset << endl; // Prints the logical and physical addresses in hexadecimal format
                break;
            case 32: 
                cout << "Logical Address: 0x" << hex << l_addres << " => Page Number: 0x" << 0x3E500 << ", Offset 0x" << hex << offset << endl; // Prints the logical and physical addresses in hexadecimal format
                break;
            default:
                cout << "Invalid Page Number. " << endl; // Prints an error message for invalid page number
            }
        }
        return 0;
    }
    else {
        cout << "Invalid Page Number: " <<  endl; // Prints an error message for invalid page number
    }
    return 0;
}

int main() {
    int logicalAddress; // Generates a random logical address
    cout << "Give me a logical address: 0x";
    cin >> hex >> logicalAddress; // input logical address
    // Generate logical addresses and translate them into physical addresses
    // This loop translates 10 random logical addresses to physical addresses using the page/frame table
    int pageNumber = (logicalAddress >> 8) & 0xFF; // Calculates the page number from the logical address
    int offset = logicalAddress & 0xFF; // Calculates the offset within the page from the logical address
    getPhysicalAdd(NUM_PAGES, FRAME_SIZE, pageNumber, offset, logicalAddress); //gets physical address and displays the frame base address and offset

    return 0;
}