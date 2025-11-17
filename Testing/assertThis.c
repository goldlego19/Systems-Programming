 #include <stdio.h>
 #include <assert.h>
 int main(int argc, char *argv[])
 {
	  unsigned int age;
	  printf("Enter your age: ");
	  scanf("%d", &age);
	  assert(age < 120);
	  printf("Goodbye\n");
	  return 0;
}
