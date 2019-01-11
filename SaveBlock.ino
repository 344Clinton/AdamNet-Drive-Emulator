int SaveBlock(unsigned long blocknumber, byte devicenumber){                // Save the buffer array to the SD card
  digitalWrite(statusled[devicenumber-4],HIGH);// Turn on the status LED
  int remainder = blocknumber % 4;
  file.open(sd.vwd(),filesindex[MountedFile[devicenumber-4]], O_READ | O_WRITE);
  Serial.print("D");
  Serial.print(devicenumber - 3);
  Serial.print(": Writing: ");
  Serial.println(blocknumber);
  unsigned long blocklocation = blocknumber*0x00000400;
  file.seekSet(blocklocation);
  if (typeindex[MountedFile[devicenumber-4]] == 0){  // Is this a disk?
    for (int i=3; i<=514;i++){
        file.write(blockdata[devicenumber-4][i]);
    }
    if (remainder==0||remainder==1){
      file.seekSet((blocknumber*0x400)+(interleave * 0x200));
      for (int i=515; i<=1026;i++){
        file.write(blockdata[devicenumber-4][i]);
      }
    }
    else{
      file.seekSet((blocknumber*0x400)-(0x1000-(interleave * 0x200)));
      for (int i=515; i<=1026;i++){
        file.write(blockdata[devicenumber-4][i]);
      }
    }
  }
  if (typeindex[MountedFile[devicenumber-4]] == 1){  // Is this a DDP?
    for (int i=3; i<=1026;i++){
        file.write(blockdata[devicenumber-4][i]);
    }
  }
  file.close();
  digitalWrite(statusled[devicenumber-4],LOW);// Turn off the status LED  
  return 1;
}
