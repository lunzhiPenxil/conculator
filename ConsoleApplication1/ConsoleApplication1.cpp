#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include "stdafx.h"

struct DATA;
struct DATALIST;
struct LISTDETAIL;
struct LISTDETAIL;

void AddDATALIST(struct DATALIST **f, struct DATA *in);
DATALIST* scan2LIST(DATA *in_head, DATA *in_last);
double getnum(DATA *head, DATA *last);

struct DATA
{
	char text;
	DATA *pre;
	DATA *next;
	void AddNext(char in)
	{
		struct DATA *p;
		p = (struct DATA *)malloc(sizeof(struct DATA));
		p->pre = this;
		if (this->next != NULL)
		{
			p->next = this->next;
			this->next->pre = p;
		}
		else
		{
			p->next = NULL;
		}
		this->next = p;
		p->text = in;
	}
	void AddPre(char in)
	{
		struct DATA *p;
		p = (struct DATA *)malloc(sizeof(struct DATA));
		p->next = this;
		if (this->pre != NULL)
		{
			p->pre = this->pre;
			this->pre->next = p;
		}
		else
		{
			p->pre = NULL;
		}
		this->pre = p;
		p->text = in;
	}
	void printl()
	{
		struct DATA *p = this;
		do
		{
			printf("%c", p->text);
			p = p->next == NULL ? p : p->next;
		} while (p->next != NULL);
		if (p != this)
		{
			printf("%c", p->text);
		}
	}
};

struct DATALIST
{
	DATA *head;
	DATA *last;
	DATA *mark;
	DATA *back;
	DATALIST *pre;
	DATALIST *next;
	void AddNext(struct DATA *in)
	{
		struct DATALIST *p;
		p = (struct DATALIST *)malloc(sizeof(struct DATALIST));
		p->head = in;
		if (in != NULL)
		{
			DATA *f2 = in;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			p->last = f2;
		}
		else
		{
			p->last = NULL;
		}
		p->pre = this;
		if (this->next != NULL)
		{
			p->next = this->next;
			this->next->pre = p;
		}
		else
		{
			p->next = NULL;
		}
		this->next = p;
	}
	void AddPre(struct DATA *in)
	{
		struct DATALIST *p;
		p = (struct DATALIST *)malloc(sizeof(struct DATALIST));
		p->head = in;
		if (in != NULL)
		{
			DATA *f2 = in;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			p->last = f2;
		}
		else
		{
			p->last = NULL;
		}
		p->next = this;
		if (this->pre != NULL)
		{
			p->pre = this->pre;
			this->pre->next = p;
		}
		else
		{
			p->pre = NULL;
		}
		this->pre = p;
	}
	void SetLine(char *line)
	{
		if (this->head != NULL)
		{
			DATA *f1, *f2;
			f1 = this->head;
			while (f1 != NULL)
			{
				f2 = f1->next;
				free(f1);
				f1 = f2;
			}
		}
		char *f;
		struct DATA *p1 = NULL;
		struct DATA *p2 = NULL;
		for (f = line; *f != '\0'; f++)
		{
			p1 = (struct DATA *)malloc(sizeof(struct DATA));
			p1->text = *f;
			p1->pre = p2;
			p1->pre == NULL ? 0 : p1->pre->next = p1;
			p1->next = NULL;
			p2 = p1;
		}
		for (; !(p1->pre == NULL); p1 = p1->pre);
		this->head = p1;
		if (p1 != NULL)
		{
			DATA *f2 = p1;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			this->last = f2;
		}
		else
		{
			this->last = NULL;
		}
	}
	void SetLineNext(char *line)
	{
		if (this->next == NULL)
		{
			this->AddNext(NULL);
		}
		this->next->SetLine(line);
	}
	void SetLinePre(char *line)
	{
		if (this->pre == NULL)
		{
			this->AddPre(NULL);
		}
		this->pre->SetLine(line);
	}
	void printl()
	{
		this->head->printl();
	}
	void printd()
	{
		DATALIST *f = this;
		do
		{
			f->head->printl();
			printf("\n");
			f = f->next == NULL ? f : f->next;
		} while (f->next != NULL);
		if (f != this)
		{
			f->head->printl();
			printf("\n");
		}
	}
	int DATALIST2str(char **out)
	{
		if (this->head == NULL)
		{
			out = NULL;
			return 0;
		}
		else
		{
			DATA *f = this->head;
			int n = 0;
			char *fs;
			for (;; f = f->next)
			{
				n++;
				if (f == this->last)
				{
					break;
				}
			}
			*out = (char *)malloc(sizeof(char)*(n + 1));
			fs = *out;
			f = this->head;
			for (;; f = f->next, fs++)
			{
				*fs = f->text;
				if (f == this->last)
				{
					break;
				}
			}
			fs++;
			*fs = '\0';
			return 1;
		}
	}
	void stroutal(char **out)
	{
		long long n_list = 0, n_data = 0;
		DATALIST *f_list = this;
		DATA *f_data =NULL;
		for (;;f_list=f_list->next)
		{
			n_list++;
			if (f_list->head == NULL)
			{
				if (f_list->next == NULL)
				{
					break;
				}
				continue;
			}
			for (f_data = f_list->head;;f_data=f_data->next)
			{
				n_data++;
				if (f_data == f_list->last)
				{
					break;
				}
			}
			if (f_list->next == NULL)
			{
				break;
			}
		}
		char *loc = (char *)malloc(sizeof(char)*(n_list+n_data+1));
		char *f_loc = loc;
		*out = loc;
		for (f_list = this;; f_list = f_list->next,f_loc++)
		{
			if (f_list->head == NULL)
			{
				*f_loc = '\n';
				if (f_list->next == NULL)
				{
					break;
				}
				continue;
			}
			for (f_data = f_list->head;; f_data = f_data->next,f_loc++)
			{
				*f_loc = f_data->text;
				if (f_data == f_list->last)
				{
					break;
				}
			}
			f_loc++;
			*f_loc = '\n';
			if (f_list->next == NULL)
			{
				break;
			}
		}
		f_loc++;
		*f_loc = '\0';
	}
	char read(long long num_list_t, long long num_data_t)
	{
		DATALIST *list = this;
		DATA *data;
		long long num_list = num_list_t, num_data = num_data_t;
		if (num_list == 0)
		{
			//暂无
		}
		else if (num_list>0)
		{
			for (; num_list != 0; num_list--)
			{
				if (list->next == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:list_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					list = list->next;
				}
			}
		}
		else if (num_list<0)
		{
			for (; num_list != 0; num_list++)
			{
				if (list->pre == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:list_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					list = list->pre;
				}
			}
		}
		data = list->head;
		if (num_data == 0)
		{
			//暂无
		}
		else if (num_data>0)
		{
			//for(;num_data!=0;data=data->next,num_data--);
			for (; num_data != 0; num_data--)
			{
				if (data->next == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:data_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					data = data->next;
				}
			}
		}
		else if (num_data<0)
		{
			//for(;num_data!=0;data=data->pre,num_data++);
			for (; num_data != 0; num_data++)
			{
				if (data->pre == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:data_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					data = data->pre;
				}
			}
		}
		return data->text;
	}
	void ConnectLast(DATALIST *in)
	{
		DATALIST *f = this;
		if (f->next != NULL)
		{
			for (; !(f->next == NULL); f = f->next);
		}
		f->next = in;
	}
	DATALIST* getlast()
	{
		DATALIST *f1 = NULL;
		for (f1 = this;;f1=f1->next)
		{
			if (f1->next == NULL)
			{
				break;
			}
		}
		return f1;
	}
	void setNULL()
	{
		head = NULL;
		last = NULL;
		mark = NULL;
		back = NULL;
		pre = NULL;
		next = NULL;
	}
};

struct LISTDETAIL
{
	struct OFLIST
	{
		DATALIST *head;
		long long length;
	}oflist;
	struct OFSTREAM
	{
		DATALIST *loc;
		long long listloc;
	}ofstream;
	void getdetail(DATALIST *in)
	{
		DATALIST *stream_list = NULL;
		long long n_up=0, n_down=0;
		if (in->pre == NULL)
		{
			this->oflist.head = in;
			this->ofstream.listloc = 0;
		}
		else
		{
			DATALIST *f_up = NULL;
			for (f_up = in;;f_up=f_up->pre)
			{
				if (f_up->pre == NULL)
				{
					break;
				}
				n_up++;
			}
			this->oflist.head = f_up;
			this->ofstream.listloc = n_up;
		}
		if (in->next == NULL)
		{
			//暂无
		}
		else
		{
			DATALIST *f_down = NULL;
			for (f_down = in;; f_down = f_down->next)
			{
				if (f_down->next == NULL)
				{
					break;
				}
				n_down++;
			}
		}
		this->oflist.length = n_up + n_down + 1;
		this->ofstream.loc = in;
	}
	void printal()
	{
		printf("\n---LISTDETAIL---\n OFLIST:\n  head=%x\n  length=%lld\n OFSTREAM\n  loc=%x\n  listloc=%lld\n", this->oflist.head, this->oflist.length, this->ofstream.loc, this->ofstream.listloc);
	}
};

struct DATADETAIL
{
	struct OFDATA
	{
		DATA *head;
		DATA *last;
		long long length;
	}ofdata;
	struct OFSTREAM
	{
		DATALIST *loc;
	}ofstream;
	void getdetail(DATALIST *in)
	{
		this->ofstream.loc = in;
		this->ofdata.head = in->head;
		this->ofdata.last = in->last;
		if (in->head == NULL)
		{
			this->ofdata.length = 0;
		}
		else
		{
			DATA *f=in->head;
			long long n = 0;
			for (;;f=f->next)
			{
				n++;
				if (f == in->last)
				{
					break;
				}
			}
			this->ofdata.length = n;
		}
	}
	void printal()
	{
		printf("\n---DATADETAIL---\n OFDATA:\n  head=%x\n  last=%x\n  length=%lld\n OFSTREAM\n  loc=%x\n", this->ofdata.head, this->ofdata.last, this->ofdata.length, this->ofstream.loc);
	}
};

void AddDATALIST(struct DATALIST **f1, struct DATA *in)
{
	struct DATALIST *f = (struct DATALIST *)malloc(sizeof(struct DATALIST));
	f->head = in;
	if (in != NULL)
	{
		DATA *f2 = in;
		for (;; f2 = f2->next)
		{
			if (f2->next == NULL)
			{
				break;
			}
		}
		f->last = f2;
	}
	else
	{
		f->last = NULL;
	}
	f->pre = NULL;
	f->next = NULL;
	f->mark = NULL;
	f->back = NULL;
	*f1 = f;
}


int main()
{
	char table1[] = { '0','1','2','3','4','5','6','7','8','9' };
	char table2[] = { '+','-','*','/','\\','^' };
	char table3[] = { '(',')' };
	char *str1;

	DATALIST *L1;
	AddDATALIST(&L1, NULL);
	DATALIST *f1 = L1;
	f1->SetLine("123.456");
	printf("%lf\n", getnum(f1->head, f1->last));
	/*DATALIST *s1 = scan2LIST(f1->head, f1->last);
	char *f = NULL;
	s1->stroutal(&f);
	printf("%s", f);*/

}

DATALIST* scan2LIST(DATA *in_head,DATA *in_last)
{
	char table1[] = { '0','1','2','3','4','5','6','7','8','9' };
	char table2[] = { '+','-','*','/','\\','^' };
	char table3[] = { '(',')' };
	DATALIST *out = (DATALIST *)malloc(sizeof(DATALIST));
	DATA *f1 = NULL, *f2 = NULL, *f_head = NULL, *f_last = NULL;

	out->pre = NULL;
	out->next = NULL;
	out->mark = NULL;
	out->back = NULL;
	out->head = NULL;
	out->last = NULL;

	int n_on_1 = 0, n_on_2 = 0, n_on_3 = 0;
	int n_1=0,n_2=0,n_3 = 0;

	for (f1 = in_head;; f1 = f1->next)
	{
		if (f1->text == table3[0])
		{
			if (n_on_3 == 0)
			{
				n_on_3 = 1;
				f_head = f1;
			}
			n_3++;
		}
		else if (f1->text == table3[1])
		{
			n_3--;
		}
		if (n_on_3 == 1&&n_3==0)
		{
			f_last = f1;
			out->head = f_head->next;
			out->last = f_last->pre;
			out->ConnectLast(scan2LIST(out->head, out->last));//纵向递归
			out->ConnectLast(f_last == in_last ? NULL : scan2LIST(f_last->next, in_last));//横向递归
			break;
		}
		if (f1 == in_last)
		{
			break;
		}
	}

	return out;
}

double calculator(DATA *head,DATA *last)
{
	DATALIST *in = scan2LIST(head,last);
	DATA *f1 = NULL;
	DATALIST A,B;A.setNULL();B.setNULL();
	double n1 = 0;
	int re_A = 0, re_B = 0;


	for (f1 = head;; f1 = f1->next)
	{
		if ((f1->text >= '0'&&f1->text >= '9') || f1->text == '.')
		{
			if (re_A == 0)
			{
				A.head = f1;
			}
		}
		if (f1 == last)
		{
			break;
		}
	}

	return NULL;
}

double getnum(DATA *head, DATA *last)
{
	DATA *f1 = head;
	double out = 0, n1 = 0;
	int on = 0;
	for (;; f1 = f1->next)
	{
		if (f1->text == '.')
		{
			on++;
		}
		else if (on == 0)
		{
			n1 = (double)(f1->text) - 48;
			out = out * 10 + n1;
		}
		else if (on != 0)
		{
			n1 = (double)(f1->text) - 48;
			n1 *= pow(10, -on);
			on++;
			out += n1;
		}
		if (f1 == last)
		{
			break;
		}
	}
	return out;
}
