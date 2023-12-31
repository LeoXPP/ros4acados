# matrix and vector structures
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_strmat/blasfeo_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_strmat/blasfeo_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_strvec/blasfeo_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_strvec/blasfeo_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/memory_size/memsize/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/DMATEL_LIBSTR/BLASFEO_DMATEL/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/SMATEL_LIBSTR/BLASFEO_SMATEL/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/DVECEL_LIBSTR/BLASFEO_DVECEL/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/SVECEL_LIBSTR/BLASFEO_SVECEL/g' {} \;
# aux_ext_dep
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_allocate_strmat/blasfeo_allocate_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_allocate_strmat/blasfeo_allocate_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_allocate_strvec/blasfeo_allocate_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_allocate_strvec/blasfeo_allocate_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_free_strmat/blasfeo_free_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_free_strmat/blasfeo_free_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_free_strvec/blasfeo_free_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_free_strvec/blasfeo_free_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_strmat/blasfeo_print_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_strmat/blasfeo_print_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_e_strmat/blasfeo_print_exp_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_e_strmat/blasfeo_print_exp_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_to_file_strmat/blasfeo_print_to_file_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_to_file_strmat/blasfeo_print_to_file_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_strvec/blasfeo_print_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_strvec/blasfeo_print_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_e_strvec/blasfeo_print_exp_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_e_strvec/blasfeo_print_exp_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_to_file_strvec/blasfeo_print_to_file_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_to_file_strvec/blasfeo_print_to_file_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_tran_strvec/blasfeo_print_tran_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_tran_strvec/blasfeo_print_tran_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_e_tran_strvec/blasfeo_print_exp_tran_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_e_tran_strvec/blasfeo_print_exp_tran_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_print_tran_to_file_strvec/blasfeo_print_to_file_tran_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_print_tran_to_file_strvec/blasfeo_print_to_file_tran_svec/g' {} \;
# aux
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_create_strmat/blasfeo_create_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_create_strmat/blasfeo_create_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_create_strvec/blasfeo_create_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_create_strvec/blasfeo_create_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_size_strmat/blasfeo_memsize_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_size_strmat/blasfeo_memsize_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_size_diag_strmat/blasfeo_memsize_diag_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_size_diag_strmat/blasfeo_memsize_diag_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_size_strvec/blasfeo_memsize_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_size_strvec/blasfeo_memsize_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_mat2strmat/blasfeo_pack_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_mat2strmat/blasfeo_pack_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_vec2strvec/blasfeo_pack_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_vec2strvec/blasfeo_pack_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_tran_mat2strmat/blasfeo_pack_tran_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_tran_mat2strmat/blasfeo_pack_tran_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_tran_strmat2mat/blasfeo_unpack_tran_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_tran_strmat2mat/blasfeo_unpack_tran_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_strmat2mat/blasfeo_unpack_smat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_strmat2mat/blasfeo_unpack_dmat/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/d_cvt_strvec2vec/blasfeo_unpack_dvec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/s_cvt_strvec2vec/blasfeo_unpack_svec/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgein1_libstr/blasfeo_dgein1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/agein1_libstr/blasfeo_agein1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/blasfeo_agein1/blasfeo_sgein1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgein1_libstr/blasfeo_sgein1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgeex1_libstr/blasfeo_dgeex1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgeex1_libstr/blasfeo_sgeex1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecin1_libstr/blasfeo_dvecin1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecin1_libstr/blasfeo_svecin1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecex1_libstr/blasfeo_dvecex1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecex1_libstr/blasfeo_svecex1/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgese_libstr/blasfeo_dgese/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgese_libstr/blasfeo_sgese/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecse_libstr/blasfeo_dvecse/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecse_libstr/blasfeo_svecse/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgecp_libstr/blasfeo_dgecp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgecp_libstr/blasfeo_sgecp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgesc_libstr/blasfeo_dgesc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgesc_libstr/blasfeo_sgesc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgecpsc_libstr/blasfeo_dgecpsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgecpsc_libstr/blasfeo_sgecpsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dveccp_libstr/blasfeo_dveccp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sveccp_libstr/blasfeo_sveccp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecsc_libstr/blasfeo_dvecsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecsc_libstr/blasfeo_svecsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dveccpsc_libstr/blasfeo_dveccpsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sveccpsc_libstr/blasfeo_sveccpsc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrcp_l_libstr/blasfeo_dtrcp_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strcp_l_libstr/blasfeo_strcp_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsc_l_libstr/blasfeo_dtrsc_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsc_l_libstr/blasfeo_strsc_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrcpsc_l_libstr/blasfeo_dtrcpsc_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strcpsc_l_libstr/blasfeo_strcpsc_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgead_libstr/blasfeo_dgead/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgead_libstr/blasfeo_sgead/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecad_libstr/blasfeo_dvecad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecad_libstr/blasfeo_svecad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgetr_libstr/blasfeo_dgetr/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgetr_libstr/blasfeo_sgetr/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrtr_l_libstr/blasfeo_dtrtr_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strtr_l_libstr/blasfeo_strtr_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrtr_u_libstr/blasfeo_dtrtr_u/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strtr_u_libstr/blasfeo_strtr_u/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiare_libstr/blasfeo_ddiare/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiare_libstr/blasfeo_sdiare/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiain_libstr/blasfeo_ddiain/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiain_libstr/blasfeo_sdiain/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiain_sp_libstr/blasfeo_ddiain_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiain_sp_libstr/blasfeo_sdiain_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiaex_libstr/blasfeo_ddiaex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiaex_libstr/blasfeo_sdiaex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiaex_sp_libstr/blasfeo_ddiaex_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiaex_sp_libstr/blasfeo_sdiaex_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiaad_libstr/blasfeo_ddiaad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiaad_libstr/blasfeo_sdiaad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiaad_sp_libstr/blasfeo_ddiaad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiaad_sp_libstr/blasfeo_sdiaad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddiaadin_sp_libstr/blasfeo_ddiaadin_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdiaadin_sp_libstr/blasfeo_sdiaadin_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowin_libstr/blasfeo_drowin/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowin_libstr/blasfeo_srowin/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowex_libstr/blasfeo_drowex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowex_libstr/blasfeo_srowex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowad_libstr/blasfeo_drowad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowad_libstr/blasfeo_srowad/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowad_sp_libstr/blasfeo_drowad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowad_sp_libstr/blasfeo_srowad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowsw_libstr/blasfeo_drowsw/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowsw_libstr/blasfeo_srowsw/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowpe_libstr/blasfeo_drowpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowpe_libstr/blasfeo_srowpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowpei_libstr/blasfeo_drowpei/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowpei_libstr/blasfeo_srowpei/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolin_libstr/blasfeo_dcolin/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolin_libstr/blasfeo_scolin/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolex_libstr/blasfeo_dcolex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolex_libstr/blasfeo_scolex/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolsw_libstr/blasfeo_dcolsw/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolsw_libstr/blasfeo_scolsw/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolpe_libstr/blasfeo_dcolpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolpe_libstr/blasfeo_scolpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolpei_libstr/blasfeo_dcolpei/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolpei_libstr/blasfeo_scolpei/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecad_sp_libstr/blasfeo_dvecad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecad_sp_libstr/blasfeo_svecad_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecin_sp_libstr/blasfeo_dvecin_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecin_sp_libstr/blasfeo_svecin_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecex_sp_libstr/blasfeo_dvecex_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecex_sp_libstr/blasfeo_svecex_sp/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dveccl_libstr/blasfeo_dveccl/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sveccl_libstr/blasfeo_sveccl/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dveccl_mask_libstr/blasfeo_dveccl_mask/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sveccl_mask_libstr/blasfeo_sveccl_mask/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecze_libstr/blasfeo_dvecze/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecze_libstr/blasfeo_svecze/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecnrm_inf_libstr/blasfeo_dvecnrm_inf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecnrm_inf_libstr/blasfeo_svecnrm_inf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecpe_libstr/blasfeo_dvecpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecpe_libstr/blasfeo_svecpe/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecpei_libstr/blasfeo_dvecpei/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecpei_libstr/blasfeo_svecpei/g' {} \;
# blas 1
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/daxpy_libstr/blasfeo_daxpy/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/saxpy_libstr/blasfeo_saxpy/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/daxpby_libstr/blasfeo_daxpby/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/saxpby_libstr/blasfeo_saxpby/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecmulacc_libstr/blasfeo_dvecmulacc/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecmulacc_libstr/blasfeo_svecmulacc/g' {} \;
#find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dvecmuldot_libstr/blasfeo_dvecmuldot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/svecmuldot_libstr/blasfeo_svecmuldot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ddot_libstr/blasfeo_ddot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sdot_libstr/blasfeo_sdot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drotg_libstr/blasfeo_drotg/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srotg_libstr/blasfeo_srotg/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dcolrot_libstr/blasfeo_dcolrot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/scolrot_libstr/blasfeo_scolrot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/drowrot_libstr/blasfeo_drowrot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/srowrot_libstr/blasfeo_srowrot/g' {} \;
# blas 2
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemv_n_libstr/blasfeo_dgemv_n/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemv_n_libstr/blasfeo_sgemv_n/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemv_t_libstr/blasfeo_dgemv_t/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemv_t_libstr/blasfeo_sgemv_t/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemv_nt_libstr/blasfeo_dgemv_nt/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemv_nt_libstr/blasfeo_sgemv_nt/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemv_diag_libstr/blasfeo_dgemv_d/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemv_diag_libstr/blasfeo_sgemv_d/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_lnn_mn_libstr/blasfeo_dtrsv_lnn_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_lnn_mn_libstr/blasfeo_strsv_lnn_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_ltn_mn_libstr/blasfeo_dtrsv_ltn_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_ltn_mn_libstr/blasfeo_strsv_ltn_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_lnn_libstr/blasfeo_dtrsv_lnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_lnn_libstr/blasfeo_strsv_lnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_lnu_libstr/blasfeo_dtrsv_lnu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_lnu_libstr/blasfeo_strsv_lnu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_ltn_libstr/blasfeo_dtrsv_ltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_ltn_libstr/blasfeo_strsv_ltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_ltu_libstr/blasfeo_dtrsv_ltu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_ltu_libstr/blasfeo_strsv_ltu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_unn_libstr/blasfeo_dtrsv_unn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_unn_libstr/blasfeo_strsv_unn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsv_utn_libstr/blasfeo_dtrsv_utn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsv_utn_libstr/blasfeo_strsv_utn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmv_unn_libstr/blasfeo_dtrmv_unn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmv_unn_libstr/blasfeo_strmv_unn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmv_utn_libstr/blasfeo_dtrmv_utn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmv_utn_libstr/blasfeo_strmv_utn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmv_lnn_libstr/blasfeo_dtrmv_lnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmv_lnn_libstr/blasfeo_strmv_lnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmv_ltn_libstr/blasfeo_dtrmv_ltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmv_ltn_libstr/blasfeo_strmv_ltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dsymv_l_libstr/blasfeo_dsymv_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ssymv_l_libstr/blasfeo_ssymv_l/g' {} \;
# blas 3
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemm_nt_libstr/blasfeo_dgemm_nt/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemm_nt_libstr/blasfeo_sgemm_nt/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemm_nn_libstr/blasfeo_dgemm_nn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemm_nn_libstr/blasfeo_sgemm_nn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dsyrk_ln_libstr/blasfeo_dsyrk_ln/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ssyrk_ln_libstr/blasfeo_ssyrk_ln/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dsyrk_ln_mn_libstr/blasfeo_dsyrk_ln_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ssyrk_ln_mn_libstr/blasfeo_ssyrk_ln_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmm_rutn_libstr/blasfeo_dtrmm_rutn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmm_rutn_libstr/blasfeo_strmm_rutn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrmm_rlnn_libstr/blasfeo_dtrmm_rlnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strmm_rlnn_libstr/blasfeo_strmm_rlnn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsm_rltn_libstr/blasfeo_dtrsm_rltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsm_rltn_libstr/blasfeo_strsm_rltn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsm_rltu_libstr/blasfeo_dtrsm_rltu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsm_rltu_libstr/blasfeo_strsm_rltu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsm_rutn_libstr/blasfeo_dtrsm_rutn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsm_rutn_libstr/blasfeo_strsm_rutn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsm_llnu_libstr/blasfeo_dtrsm_llnu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsm_llnu_libstr/blasfeo_strsm_llnu/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dtrsm_lunn_libstr/blasfeo_dtrsm_lunn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/strsm_lunn_libstr/blasfeo_strsm_lunn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemm_l_diag_libstr/blasfeo_dgemm_dn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemm_l_diag_libstr/blasfeo_sgemm_dn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgemm_r_diag_libstr/blasfeo_dgemm_nd/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgemm_r_diag_libstr/blasfeo_sgemm_nd/g' {} \;
# lapack
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dpotrf_l_libstr/blasfeo_dpotrf_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/spotrf_l_libstr/blasfeo_spotrf_l/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dpotrf_l_mn_libstr/blasfeo_dpotrf_l_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/spotrf_l_mn_libstr/blasfeo_spotrf_l_mn/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dsyrk_dpotrf_ln_libstr/blasfeo_dsyrk_dpotrf_ln/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/ssyrk_spotrf_ln_libstr/blasfeo_ssyrk_spotrf_ln/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgetrf_nopivot_libstr/blasfeo_dgetrf_nopivot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgetrf_nopivot_libstr/blasfeo_sgetrf_nopivot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgetrf_libstr/blasfeo_dgetrf_rowpivot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgetrf_libstr/blasfeo_sgetrf_rowpivot/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgeqrf_libstr/blasfeo_dgeqrf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgeqrf_libstr/blasfeo_sgeqrf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgeqrf_work_size_libstr/blasfeo_dgeqrf_worksize/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgeqrf_work_size_libstr/blasfeo_sgeqrf_worksize/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgelqf_libstr/blasfeo_dgelqf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgelqf_libstr/blasfeo_sgelqf/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/dgelqf_work_size_libstr/blasfeo_dgelqf_worksize/g' {} \;
find ./ -type f -not -path "*git*" -not -path "*change_name*" -exec sed -i 's/sgelqf_work_size_libstr/blasfeo_sgelqf_worksize/g' {} \;
