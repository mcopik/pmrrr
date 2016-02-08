/* Copyright (c) 2010, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are permitted provided that the following
 * conditions are met:
 *   * Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the following
 *     disclaimer.
 *   * Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials 
 *     provided with the distribution.
 *   * Neither the name of the RWTH Aachen University nor the
 *     names of its contributors may be used to endorse or promote 
 *     products derived from this software without specific prior 
 *     written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL RWTH 
 * AACHEN UNIVERSITY BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 *
 * Coded by Matthias Petschow (petschow@aices.rwth-aachen.de),
 * August 2010, Version 0.6
 *
 * This code was the result of a collaboration between 
 * Matthias Petschow and Paolo Bientinesi. When you use this 
 * code, kindly reference a paper related to this work.
 *
 */

#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "rrr.h"
#include "global.h"

namespace pmrrr { namespace detail {

	template<typename FloatingType>
	rrr_t<FloatingType> *PMR_create_rrr(FloatingType *restrict D, FloatingType *restrict L,
				  FloatingType *restrict DL, FloatingType *restrict DLL,
				  int size, int depth)
	{
	  int   info;
	  rrr_t<FloatingType> *RRR;

	  RRR = (rrr_t<FloatingType> *) malloc( sizeof(rrr_t<FloatingType>) );
	  assert(RRR != NULL);

	  RRR->D                 = D;
	  RRR->L                 = L;
	  RRR->DL                = DL;
	  RRR->DLL               = DLL;
	  RRR->size              = size;
	  RRR->depth             = depth;
	  RRR->parent_processed  = false;
	  RRR->copied_parent_rrr = false;
	  RRR->ndepend           = 0;

	  info = pthread_mutex_init(&RRR->mutex, NULL);
	  assert(info == 0);

	  return(RRR);
	}


	template<typename FloatingType>
	rrr_t<FloatingType> *PMR_reset_rrr(rrr_t<FloatingType> *RRR, FloatingType *restrict D, 
				 FloatingType *restrict L, FloatingType *restrict DL, 
				 FloatingType *restrict DLL, int size, int depth)
	{
	  RRR->D                = D;
	  RRR->L                = L;
	  RRR->DL               = DL;
	  RRR->DLL              = DLL;
	  RRR->size             = size;
	  RRR->depth            = depth;
	  RRR->parent_processed = false;

	  return(RRR);
	}


	template<typename FloatingType>
	int PMR_increment_rrr_dependencies(rrr_t<FloatingType> *RRR)
	{
	  /* returns number of dependencies */
	  int i, info;

	  info = pthread_mutex_lock(&RRR->mutex);
	  assert(info == 0);
	  
	  RRR->ndepend++;
	  i = RRR->ndepend;
	  
	  info = pthread_mutex_unlock(&RRR->mutex);
	  assert(info == 0);
	  
	  return(i);
	}


	template<typename FloatingType>
	int PMR_set_parent_processed_flag(rrr_t<FloatingType> *RRR)
	{
	  int info;
	  
	  info = pthread_mutex_lock(&RRR->mutex);
	  assert(info == 0);
	  
	  RRR->parent_processed = true;
	  
	  info = pthread_mutex_unlock(&RRR->mutex);
	  assert(info == 0);

	  return(info);
	}


	template<typename FloatingType>
	int PMR_set_copied_parent_rrr_flag(rrr_t<FloatingType> *RRR, bool val)
	{
	  int info;
	  
	  info = pthread_mutex_lock(&RRR->mutex);
	  assert(info == 0);
	  
	  RRR->copied_parent_rrr = val;
	  
	  info = pthread_mutex_unlock(&RRR->mutex);
	  assert(info == 0);

	  return(info);
	}


	template<typename FloatingType>
	int PMR_try_destroy_rrr(rrr_t<FloatingType> *RRR)
	{
	  /* return 0 on success, otherwise 1 */
	  
	  int info, tmp=0;

	  info = pthread_mutex_lock(&RRR->mutex);
	  assert(info == 0);

	  RRR->ndepend--;

	  if (RRR->ndepend == 0 &&
		  RRR->parent_processed == true) {

		if (RRR->depth >0) {
		  free(RRR->D);
		  free(RRR->L);
		}

		if (RRR->depth >=0) {
		  free(RRR->DL);
		  free(RRR->DLL);
		}
		
		tmp = 1;
	  }
	  
	  info = pthread_mutex_unlock(&RRR->mutex);
	  assert(info == 0);

	  if (tmp == 1) {
		free(RRR);
		return(0);
	  } else {
		return(1);
	  }
	}

}	// detail

}	// pmrrr
