#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct bpb_com {
    uint8_t bs_jmpboot[3];
    uint8_t bs_oemname[8];
    uint16_t bpb_bytspersec;
    uint8_t bpb_secperclus;
    uint16_t bpb_rsvdseccnt;
    uint8_t bpb_numfats;
    uint16_t bpb_rootentcnt;
    uint16_t bpb_totsec16;
    uint8_t bpb_media;
    uint16_t bpb_fatsz16;
    uint16_t bpb_secpertrk;
    uint16_t bpb_numheads;
    uint32_t bpb_hiddsec;
    uint32_t bpb_totsec32;
} __attribute__((packed));

struct bpb_ext {
    uint8_t bs_drvnum;
    uint8_t bs_reserved1;
    uint8_t bs_bootsig;
    uint8_t bs_volid[4];
    uint8_t bs_vollab[11];
    uint8_t bs_filsystype[8];
}__attribute__((packed));

struct bpb {
    struct bpb_com bpb_com;
    struct bpb_ext bpb_ext;
} __attribute__((packed));


static int readBPB(struct bpb *bpb, const char *imgName);
static int printBPB(struct bpb *bpb);

int main(int argc, char **argv)
{

    if (argc != 2) {
	fprintf(stderr, "Usage: %s fatImgName\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    struct bpb bpb = {'\0'};
    if (!readBPB(&bpb, argv[1]))
	return EXIT_FAILURE;
    printBPB(&bpb);

    return EXIT_SUCCESS;
}

static int 
readBPB(struct bpb *bpb, const char *imgName)
{
    FILE *fp;

    if (!bpb || !fp)
	return 0;

    if (!(fp = fopen(imgName, "rb"))) {
	fprintf(stderr, "Could not open %s\n", imgName);
	return(0);
    }

    if (fread(bpb, sizeof(struct bpb), 1, fp) != 1) {
	fprintf(stderr, "Error reading %s\n", imgName);
	return(0);
    }

    if (fp)
	fclose(fp);

    return 1;
}

static int
printBPB(struct bpb *bpb)
{
    printf("Common BPB structure (FAT12, FAT16, FAT32):\n\n");

    printf("BS_jmpBoot: 0x%X 0x%X 0x%X\n", bpb->bpb_com.bs_jmpboot[0], 
	   bpb->bpb_com.bs_jmpboot[1], bpb->bpb_com.bs_jmpboot[2]);
    printf("BS_OEMname: %s\n", bpb->bpb_com.bs_oemname);
    printf("BPB_BytsPerSec: %d\n", bpb->bpb_com.bpb_bytspersec);
    printf("BPB_SecPerClus: %d\n", bpb->bpb_com.bpb_secperclus);
    printf("BPB_RsvdSecCnt: %d\n", bpb->bpb_com.bpb_rsvdseccnt);
    printf("BPB_NumFats: %d\n", bpb->bpb_com.bpb_numfats);
    printf("BPB_RootEntCnt: %d\n", bpb->bpb_com.bpb_rootentcnt);
    printf("BPB_TotSec16: %d\n", bpb->bpb_com.bpb_totsec16);
    printf("BPB_Media: 0x%X\n", bpb->bpb_com.bpb_media);
    printf("BPB_FATSz16: %d\n", bpb->bpb_com.bpb_fatsz16);
    printf("BPB_SecPerTrk: %d\n", bpb->bpb_com.bpb_secpertrk);
    printf("BPB_NumHeads: %d\n", bpb->bpb_com.bpb_numheads);
    printf("BPB_HiddSec: %d\n", bpb->bpb_com.bpb_hiddsec);
    printf("BPB_TotSec32: %d\n", bpb->bpb_com.bpb_totsec32);

    printf("\nExtended BPB structure (FAT16, FAT32):\n\n");
    
    printf("BPB_DrvNum: 0x%X\n", bpb->bpb_ext.bs_drvnum);
    printf("BPB_reserved1: 0x%X\n", bpb->bpb_ext.bs_reserved1);
    printf("BPB_BootSig: 0x%X\n", bpb->bpb_ext.bs_bootsig);
    printf("BPB_VolID: 0x%X 0x%X 0x%X 0x%X\n", bpb->bpb_ext.bs_volid[0],
	   bpb->bpb_ext.bs_volid[1], bpb->bpb_ext.bs_volid[2],
	   bpb->bpb_ext.bs_volid[3]);
    printf("BPB_VolLab: %.*s\n", 11, bpb->bpb_ext.bs_vollab);
    printf("BPB_VolLab: %s\n", bpb->bpb_ext.bs_filsystype);

    return 1;
}
