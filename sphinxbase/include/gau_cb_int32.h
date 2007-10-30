/* -*- c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* ====================================================================
 * Copyright (c) 2007 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/**
 * \file gau_cb_int32.h
 * \author David Huggins-Daines <dhuggins@cs.cmu.edu>
 *
 * Gaussian distribution parameters (log integer computation)
 */

#ifndef __GAU_CB_INT32_H__
#define __GAU_CB_INT32_H__

#include <sphinx_config.h>
#include <cmd_ln.h>
#include <gau_cb.h>
#include <fixpoint.h>
#include <logmath.h>
#include <fe.h>

/**
 * Type representing a single density for computation.
 */
typedef struct gau_den_int32_s gau_den_int32_t;
struct gau_den_int32_s {
    int32 idx; /**< Index of Gaussian to compute. */
    int32 val; /**< Density for this Gaussian. */
};

/**
 * Read a codebook of Gaussians from mean and variance files and
 * precompute for logarithmic int32 computation.
 */
gau_cb_t *gau_cb_int32_read(
	cmd_ln_t *config,    /**< Configuration parameters */
	const char *meanfn,  /**< Filename for means */
	const char *varfn,   /**< Filename for variances */
	const char *normfn,  /**< (optional) Filename for normalization
				constants  */
        logmath_t *lmath     /**< Log-math table (for logbase, etc) */
	);

/**
 * Free a codebook loaded with gau_cb_int32_read().
 */
void gau_cb_int32_free(gau_cb_t *gau);

/**
 * Compute all floating point densities for a single feature stream in
 * an observation.
 *
 * @return the index of the highest density
 */
int gau_cb_int32_compute_all(gau_cb_t *gau, int mgau, int feat,
			     mfcc_t *obs, int32 *out_den, int worst);

/**
 * Compute a subset of floating point densities for a single feature
 * stream in an observation.
 *
 * @return the offset in inout_den of the lowest density
 */
int gau_cb_int32_compute(gau_cb_t *gau, int mgau, int feat,
			 mfcc_t *obs,
			 gau_den_int32_t *inout_den, int nden);

#ifdef FIXED_POINT
typedef fixed32 int32_mean_t; /**< Type of precomputed means for gau_cb_int32. */
typedef int32 int32_var_t; /**< Type of precomputed invvars for gau_cb_int32. */
typedef int32 int32_norm_t; /**< Type of precomputed norms for gau_cb_int32. */
#else
typedef float32 int32_mean_t; /**< Type of precomputed means for gau_cb_int32. */
typedef float32 int32_var_t; /**< Type of precomputed invvars for gau_cb_int32. */
typedef float32 int32_norm_t; /**< Type of precomputed norms for gau_cb_int32. */
#endif

/**
 * Retrieve the mean vectors from the codebook.
 */
int32_mean_t ****gau_cb_int32_get_means(gau_cb_t *gau);

/**
 * Retrieve the scaled inverse variance vectors from the codebook.
 */
int32_var_t ****gau_cb_int32_get_invvars(gau_cb_t *gau);

/**
 * Retrieve the log normalization constants from the codebook.
 */
int32_norm_t ***gau_cb_int32_get_norms(gau_cb_t *gau);


#endif /* __GAU_CB_INT32_H__ */