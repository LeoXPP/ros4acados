// CLASS_GETRF_ROWPIVOT
//

void call_routines(struct RoutineArgs *args)
	{
	// routine call
	//
	BLASFEO(ROUTINE)(
		args->m, args->n,
		args->sA_po, args->ai, args->aj,
		args->sD, args->di, args->dj,
		args->sipiv);

	BLASFEO(REF(ROUTINE))(
		args->m, args->n,
		args->rA_po, args->ai, args->aj,
		args->rD, args->di, args->dj,
		args->ripiv);
	}



void print_routine(struct RoutineArgs *args)
	{
	printf("blasfeo_%s(%d, %d, A, %d, %d, D, %d, %d, ipiv);\n", string(ROUTINE), args->m, args->n, args->ai, args->aj, args->di, args->dj);
	}



void print_routine_matrices(struct RoutineArgs *args)
	{
	printf("\nPrint A:\n");
	blasfeo_print_xmat_debug(args->m, args->n, args->sA_po, args->ai, args->aj, 0, 0, 0, "HP");
	blasfeo_print_xmat_debug(args->m, args->n, args->rA_po, args->ai, args->aj, 0, 0, 0, "REF");

	printf("\nPrint LU:\n");
	blasfeo_print_xmat_debug(args->m, args->n, args->sD, args->ai, args->aj, 0, 0, 0, "HP");
	blasfeo_print_xmat_debug(args->m, args->n, args->rD, args->ai, args->aj, 0, 0, 0, "REF");
	}



void set_test_args(struct TestArgs *targs)
	{
//	targs->ais = 1;
//	targs->bis = 1;
//	targs->dis = 1;
//	targs->xjs = 5;

	targs->nis = 13;
	targs->njs = 13;
	}
