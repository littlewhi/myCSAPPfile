void f(int a)
{
	a = a;
	a = 0;
	return;
}

int main()
{
	int a = 0x11223344;
	f(a);
	return 0;
}
