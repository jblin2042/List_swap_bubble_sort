#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
typedef struct _List {
	struct _List * next ;
	int val ;
} List ;
int Swap_list_array ( List**head , List*a , List *b ) {
	if ( ! * head || ! ( * head )->next || ! a || ! b || ( a == b ) )
		return - 1 ;
	List * p_tmp = * head ;
	int sz = 0 ;
	while ( NULL != p_tmp ) {
		++ sz ;
		p_tmp = p_tmp->next ;
	}

	List* p_array [ sz + 1 ] ;
	p_array [ sz ] = NULL ;
	int mark_a = - 1 , mark_b = - 1 , i = 0 ;
	p_tmp = * head ;
	for ( i = 0 ; i < sz ; ++ i ) {
		p_array [ i ] = p_tmp ;
		if ( a == p_tmp )
			mark_a = i ;
		else if ( b == p_tmp )
			mark_b = i ;

		p_tmp = p_tmp->next ;
	}

	if ( ( - 1 == mark_a ) || ( - 1 == mark_b ) )
		return - 2 ;
	List* p_array_tmp = p_array [ mark_a ] ;
	p_array [ mark_a ] = p_array [ mark_b ] ;
	p_array [ mark_b ] = p_array_tmp ;

	* head = p_array [ 0 ] ;
	for ( i = 0 ; i < sz ; ++ i )
		p_array [ i ]->next = p_array [ i + 1 ] ;

	return 1 ;
}

int Swap_list_normal ( List**head , List*a , List *b ) {
	if ( ! * head || ! ( * head )->next || ! a || ! b || ( a == b ) )
		return - 1 ;

	List * p_prev_a = NULL , *p_prev_b = NULL ;
	int get_node_break = 0 ;
	if ( * head == a ) {
		p_prev_a = * head ;
		get_node_break = 1 ;
	} else if ( * head == b ) {
		p_prev_b = * head ;
		get_node_break = 1 ;
	}

	List *p_curr = * head ;
	while ( p_curr ) {
		if ( p_curr->next == a ) {
			p_prev_a = p_curr ;
			++ get_node_break ;
		} else if ( p_curr->next == b ) {
			p_prev_b = p_curr ;
			++ get_node_break ;
		} else if ( 2 == get_node_break )
			break ;

		p_curr = p_curr->next ;
	}
	if ( 2 != get_node_break )
		return - 2 ;

	// head //
	if ( ( a == * head ) || ( b == * head ) ) {
		List *p_swap_node = a , *p_prev_swap_node = p_prev_a ;
		if ( a == * head ) {
			p_swap_node = b ;
			p_prev_swap_node = p_prev_b ;
		}
		p_prev_swap_node->next = * head ;
		p_prev_swap_node = ( * head )->next ;
		( * head )->next = p_swap_node->next ;
		* head = p_swap_node ;
		p_swap_node->next = p_prev_swap_node ;

		return 1 ;
	}

	p_prev_a->next = b ;
	p_prev_b->next = a ;

	p_prev_a = b->next ;
	p_prev_b = a->next ;

	b->next = p_prev_b ;
	a->next = p_prev_a ;
	return 1 ;
}

int Swap_list_circular ( List**head , List*a , List *b ) {
	if ( ! * head || ! ( * head )->next || ! a || ! b || ( a == b ) )
		return - 1 ;

	List *p_prev_a = NULL , *p_prev_b = NULL ;
	int circul = 0 ;
	if ( ( * head == a ) || ( * head == b ) )
		circul = 1 ;

	List *p_end = NULL , *p_curr = * head , *p_new_head = * head ;
	int list_sz = 0 ;
	while ( p_curr ) {
		++ list_sz ;
		if ( ! p_curr->next ) {
			p_end = p_curr ;
			if ( 1 == circul ) {
				circul = 2 ;
				p_curr->next = * head ;
			}
		}
		if ( p_curr->next == a )
			p_prev_a = p_curr ;
		else if ( p_curr->next == b )
			p_prev_b = p_curr ;

		if ( 2 == circul )
			break ;  // 最後

		p_curr = p_curr->next ;
	}
	if ( ( ! p_prev_a ) || ( ! p_prev_b ) ) {
		p_end->next = NULL ;
		return - 2 ;
	}

	// 確定最後 last node //
	if ( a == p_end )
		p_end = b ;
	else if ( b == p_end )
		p_end = a ;

	// 確認最後 head //
	if ( a == * head )
		p_new_head = b ;
	else if ( b == * head )
		p_new_head = a ;

	p_prev_a->next = b ;
	p_prev_b->next = a ;

	p_prev_a = b->next ;
	p_prev_b = a->next ;

	b->next = p_prev_b ;
	a->next = p_prev_a ;

	* head = p_new_head ;
	p_end->next = NULL ;
	return 1 ;
}

int Bubble_sort_array ( List**head ) {
	List* p_tmp = * head ;
	int sz = 0 ;
	while ( p_tmp ) {
		++ sz ;
		p_tmp = p_tmp->next ;
	}
	List* p_array [ sz + 1 ] ;
	List* p_array_tmp = NULL ;
	p_array [ sz ] = NULL ;
	p_tmp = * head ;
	int i = 0 ;
	for ( i = 0 ; i < sz ; ++ i ) {   // 重新給值
		p_array [ i ] = p_tmp ;
		p_tmp = p_tmp->next ;
	}
	int j = 0 ;
	for ( i = 0 ; i < sz - 1 ; ++ i ) {
		for ( j = 0 ; j < sz - 1 - i ; ++ j ) {
			if ( p_array [ j ]->val > p_array [ j + 1 ]->val ) {
				p_array_tmp = p_array [ j ] ;
				p_array [ j ] = p_array [ j + 1 ] ;
				p_array [ j + 1 ] = p_array_tmp ;
			}
		}
	}
	* head = p_array [ 0 ] ;
	for ( i = 0 ; i < sz ; ++ i ) {
		p_array [ i ]->next = p_array [ i + 1 ] ;
	}
	return 1 ;
}

int Bubble_sort_swap ( List**head , int (*Swap_method) ( List** , List* , List* ) ) {
	List *p_tmp = NULL , *p_bubble_end = NULL ;
	while ( p_bubble_end != * head ) {
		p_tmp = * head ;
		while ( p_tmp->next != p_bubble_end ) {
			if ( p_tmp->val > p_tmp->next->val ) {
				Swap_method ( head , p_tmp , p_tmp->next ) ;
				continue ;
			}
			p_tmp = p_tmp->next ;
		}
		p_bubble_end = p_tmp ;
	}
	return 1 ;
}

// 驗證 tools below //
#define D_array_max ( 1000 )
int Append_list ( List**head , int val [ D_array_max ] ) {
	* head = ( List* ) calloc ( 1 , sizeof(List) ) ;
	if ( NULL == * head ) {
		return - 1 ;
	}
	( * head )->val = val [ 0 ] ;
	( * head )->next = NULL ;

	List* p_tmp = NULL ;
	List* p_last = * head ;
	int i = 1 ;
	for ( ; i < D_array_max ; ++ i ) {

		p_tmp = ( List* ) calloc ( 1 , sizeof(List) ) ;
		if ( NULL == * head ) {
			return - 1 ;
		}
		p_tmp->val = val [ i ] ;
		p_tmp->next = NULL ;
		p_last->next = p_tmp ;
		p_last = p_tmp ;
	}
	return 0 ;
}
// 建立亂數資料 //
void Make_rand ( int val [ D_array_max ] ) {
	srand ( time ( NULL ) ) ;
	int i = 0 ,a = 0 ,b = 0 ,val_tmp = 0 , j = 0 ;
	for ( ; i < D_array_max ; ++ i )
		val [ i ] = i ;

	for ( j = 0 ; j < 2 ; ++ j ) {
		for ( i = 0 ; i < D_array_max ; ++ i ) {
			do {
				a = rand ( ) % D_array_max ;
				b = rand ( ) % D_array_max ;
			} while ( a == b ) ;

			val_tmp = val [ a ] ;
			val [ a ] = val [ b ] ;
			val [ b ] = val_tmp ;
		}
	}
	return ;
}

void Compare_list ( List* head ) {
	char buf [ 8912 ] = { 0 } ;
	int sz = 0 ,rtn = 0 ,i = 0 ;
	for ( i = 0 ; i < D_array_max ; ++ i ) {
		if ( i != head->val ) {
			rtn = snprintf ( buf + sz , sizeof ( buf ) - sz , "node:%p ,value:%d(i:%d)\n" , head , head->val , i ) ;
			sz += rtn ;
			if ( sz > 8900 ) {
				printf ( "%s" , buf ) ;
				sz = 0 ;
			}
		}
		head = head->next ;
	}
	printf ( "%s" , buf ) ;
	return ;
}

void Show ( List* head ) {
	char buf [ 8912 ] = { 0 } ;
	int sz = 0 , rtn = 0 ;
	while ( head ) {
		rtn = snprintf ( buf + sz , sizeof ( buf ) - sz , "value:%d ,%p\n" , head->val , head ) ;
		sz += rtn ;
		if ( sz > 8900 ) {
			printf ( "%s" , buf ) ;
			sz = 0 ;
		}
		head = head->next ;
	}
	printf ( "%s" , buf ) ;
	return ;
}


void Clear_list ( List** head ) {
	List* p_tmp = * head ;
	List* p_tmp_next = NULL ;
	while ( p_tmp ) {
		p_tmp_next = p_tmp->next ;
		free ( p_tmp ) ;
		p_tmp = NULL ;
		p_tmp = p_tmp_next ;
	}
}
// 計時器 //
struct timeval g_timer_begin ;
struct timeval g_timer_end ;
void Begin_time ( void ) {
	gettimeofday ( & g_timer_begin , NULL ) ;
	return ;
}

long double End_time ( void ) {
	gettimeofday ( & g_timer_end , NULL ) ;
	long int d_s = g_timer_end.tv_sec - g_timer_begin.tv_sec ;
	long int d_us = g_timer_end.tv_usec - g_timer_begin.tv_usec ;
	if ( g_timer_end.tv_usec < g_timer_begin.tv_usec ) {
		-- d_s ;
		d_us = ( 1000000 - g_timer_begin.tv_usec ) + g_timer_end.tv_usec ;
	}
	return d_s + ( ( long double ) d_us / 10e5 ) ;
}
int main ( void ) {

	char result_buf [ 8192 ] = { 0 } ;
	int sz = 0 , rtn = 0 ;

	int val [ D_array_max ] = { 0 } ;
	Make_rand ( val ) ;

	List * head = NULL ;

	// Bubble_sort_array //
	Append_list ( & head , val ) ;
	Begin_time ( ) ;
	Bubble_sort_array ( & head ) ;
	rtn = snprintf ( result_buf + sz , sizeof ( result_buf ) - sz , "<Bubble_sort_array> diff time:%Lf\n" , End_time ( ) ) ;
	sz += rtn ;
	Compare_list ( head ) ;
	Clear_list ( & head ) ;


	// Swap_list_array //
	Append_list ( & head , val ) ;
	Begin_time ( ) ;
	Bubble_sort_swap ( & head , Swap_list_array ) ;
	rtn = snprintf ( result_buf + sz , sizeof ( result_buf ) - sz , "<Swap_list_array> diff time:%Lf\n" , End_time ( ) ) ;
	sz += rtn ;
	Compare_list ( head ) ;
	Clear_list ( & head ) ;

	// Swap_list_normal //
	Append_list ( & head , val ) ;
	Begin_time ( ) ;
	Bubble_sort_swap ( & head , Swap_list_normal ) ;
	rtn = snprintf ( result_buf + sz , sizeof ( result_buf ) - sz , "<Swap_list_normal> diff time:%Lf\n" , End_time ( ) ) ;
	sz += rtn ;
	Compare_list ( head ) ;
	Clear_list ( & head ) ;

	// Swap_list_circular //
	Append_list ( & head , val ) ;
	Begin_time ( ) ;
	Bubble_sort_swap ( & head , Swap_list_circular ) ;
	rtn = snprintf ( result_buf + sz , sizeof ( result_buf ) - sz , "<Swap_list_circular> diff time:%Lf\n" , End_time ( ) ) ;
	sz += rtn ;
	Compare_list ( head ) ;
	Clear_list ( & head ) ;

	printf ( "%s" , result_buf ) ;
	return 0 ;
}
