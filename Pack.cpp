//
//  Pack.cpp
//  proj3
//
//  Created by John West on 10/12/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include "Pack.h"

void Pack_init(Pack *pack_ptr, const char* pack_filename)
{
	
	return;
}

void Pack_print(const Pack *pack_ptr)
{
	return;
}

Card Pack_deal_one(Pack *pack_ptr)
{
	Card next;

	next = *(pack_ptr->next);
	pack_ptr++;

	return next;
}

void Pack_reset(Pack *pack_ptr)
{
	return;
}

void Pack_shuffle(Pack *pack_ptr)
{
	return;
}