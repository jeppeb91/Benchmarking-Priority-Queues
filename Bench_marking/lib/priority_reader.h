float* read_priorities(char* filename){
	FILE* file = fopen (filename, "r" );		
	float* lines= malloc(sizeof(float)*10000);
	if ( file != NULL )
	{
		char line [16];//Line buffer size      	
		char*stop;	
		int counter = 0;		
		while ( fgets ( line, sizeof line, file ) != NULL )
      		{
         		lines[counter] = strtof(line, &stop);
			counter++;
      		}
      		fclose ( file );
   		}
	else{
		printf("Failed to read floats from file");
		return lines;
	}
   return lines;
}
