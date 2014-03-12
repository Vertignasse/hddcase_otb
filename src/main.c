#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <scsi/sg.h>
#include <inttypes.h>

#define INQ_REPLY_LEN 96
#define INQ_CMD_CODE 0x12
#define INQ_CMD_LEN 6

int main(int argc, char **argv)
 {
  int fd, rc;
  struct sg_io_hdr sg_io;

  uint8_t sense[32];
  uint8_t data[2];
  uint8_t cdb[16] = { 0xdf, 0x10, 0x00, 0x00, 0x02, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0xff}; //,0x00, 0x00, 0x00, 0x00};//

  fd = open (argv[1], O_RDWR);
  
  // set sense, data, sg_io to zero
  memset(&sg_io, 0, sizeof(struct sg_io_hdr));
  
  sg_io.interface_id = 'S';
  sg_io.cmdp = cdb;
  sg_io.cmd_len = 12;
  sg_io.dxferp = data;
  sg_io.dxfer_len = 2;
  sg_io.dxfer_direction = SG_DXFER_FROM_DEV;
  sg_io.sbp = sense;
  sg_io.mx_sb_len = sizeof(sense);
  sg_io.timeout = 5000; // 5 seconds
  
  
  rc = ioctl (fd, SG_IO, &sg_io);

  if ((data[1] & 0x01) == 0)
    printf("button is pressed\n");
  else
    printf("button is NOT pressed\n");

  return rc;
 }
