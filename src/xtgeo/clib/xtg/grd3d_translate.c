/*
 ***************************************************************************************
 *
 * NAME:
 *    grd3d_translate.c
 *
 * AUTHOR(S):
 *    Jan C. Rivenaes
 *
 * DESCRIPTION:
 *    Translate the coordinates in 3D (linear)
 *
 * ARGUMENTS:
 *    nx, ny, nx     i     Grid I J K
 *    *flip          i     Flip for X Y Z coords
 *    *shift         i     Shift for X Y Z coords
 *    p_coord_v     i/o    Coordinates vector
 *    p_zcorn_v     i/o    Corners vector
 *    debug          i     Debug level
 *
 * RETURNS:
 *    Function: 0: upon success. If problems:
 *             -1: One of the flip are not 1 or -1
 *    Geometry vectors are updated
 *
 * TODO/ISSUES/BUGS:
 *
 * LICENCE:
 *    cf. XTGeo LICENSE
 *
 * CODING STANDARD:
 *    cf. .clang-format file
 ***************************************************************************************
 */
#include "libxtg.h"
#include "logger.h"

int
grd3d_translate(int nx,
                int ny,
                int nz,
                int xflip,
                int yflip,
                int zflip,
                double xshift,
                double yshift,
                double zshift,
                double *p_coord_v,
                long ncooordin,
                double *p_zcorn_v,
                long nzcornin)

{
    /* locals */
    int i, j, ic, ib, nzcorn, iok = 0;

    logger_info(LI, FI, FU, "Do translation or pure flipping");

    if ((xflip == 1 || xflip == -1) && (yflip == 1 || yflip == -1) &&
        (zflip == 1 || zflip == -1)) {
        iok = 1;
    }

    if (iok == 0) {
        /* flip out of range */
        logger_warn(LI, FI, FU, "Error in flips ...%d %d %d", xflip, yflip, zflip);
        return (-1);
    }

    /* coord section */
    ib = 0;
    for (j = 0; j <= ny; j++) {
        for (i = 0; i <= nx; i++) {
            p_coord_v[ib + 0] = xflip * (p_coord_v[ib + 0] + xshift);
            p_coord_v[ib + 1] = yflip * (p_coord_v[ib + 1] + yshift);
            p_coord_v[ib + 2] = zflip * (p_coord_v[ib + 2] + zshift);
            p_coord_v[ib + 3] = xflip * (p_coord_v[ib + 3] + xshift);
            p_coord_v[ib + 4] = yflip * (p_coord_v[ib + 4] + yshift);
            p_coord_v[ib + 5] = zflip * (p_coord_v[ib + 5] + zshift);
            ib = ib + 6;
        }
    }

    /* zcorn section     */
    nzcorn = 4 * nx * ny * (nz + 1);
    for (ic = 0; ic <= nzcorn; ic++) {
        p_zcorn_v[ic] = zflip * (p_zcorn_v[ic] + zshift);
    }

    logger_info(LI, FI, FU, "Exit from routine");
    return (0);
}
