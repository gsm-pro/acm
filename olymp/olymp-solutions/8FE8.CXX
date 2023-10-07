#include<fstream>
#include<iomanip>
#include<vector>
#include<limits>
#define LD long double
using namespace std;
const int init_wall_size = 32;
const int init_vertices = 256;
const int init_vertex_order = 64;
const int init_3_vertices = 256;
const int init_n_vertices = 8;
const int init_delete_size = 256;
const int init_delete2_size = 256;
const int init_xsearch_size = 32;
const LD tolerance = 10. * numeric_limits<LD>::epsilon();
const LD large_number = numeric_limits<LD>::max();
const LD big_tolerance_fac = 20.;
const LD default_length = 1000.;
const int wl_hgrid = 4;
const int wl_fgrid = 8;
const int wl_hgridcu = 64;
const int wl_seq_length = 64;

template<class T>
class COMPUTER {
public:
    T &con;
    const LD boxx, boxy, boxz, xsp, ysp, zsp;
    const int hx, hy, hz, hxy, hxyz, ps;
    int **id, *co;
    LD **p;

    COMPUTER(T &con_, int hx_, int hy_, int hz_);

    ~COMPUTER() {
        delete[] qu;
        delete[] mask;
    }

    template<class V>
    bool compute_cell(V &c, int ijk, int s, int ci, int cj, int ck);

private:
    const LD bxsq;
    unsigned int mv;
    int qu_size, *qu, *qu_l;
    const unsigned int *wl;
    LD *mrad;
    unsigned int *mask;

    template<class V>
    bool corner_test(V &c, LD xl, LD yl, LD zl, LD xh, LD yh, LD zh);

    template<class V>
    inline bool edge_x_test(V &c, LD x0, LD yl, LD zl, LD x1, LD yh, LD zh);

    template<class V>
    inline bool edge_y_test(V &c, LD xl, LD y0, LD zl, LD xh, LD y1, LD zh);

    template<class V>
    inline bool edge_z_test(V &c, LD xl, LD yl, LD z0, LD xh, LD yh, LD z1);

    template<class V>
    inline bool face_x_test(V &c, LD xl, LD y0, LD z0, LD y1, LD z1);

    template<class V>
    inline bool face_y_test(V &c, LD x0, LD yl, LD z0, LD x1, LD z1);

    template<class V>
    inline bool face_z_test(V &c, LD x0, LD y0, LD zl, LD x1, LD y1);

    bool compute_min_max_radius(int di, int dj, int dk, LD fx, LD fy, LD fz, LD gx, LD gy, LD gz, LD &crs, LD mrs);

    inline void add_to_mask(int ei, int ej, int ek, int *&qu_e);

    inline void scan_bits_mask_add(unsigned int q, unsigned int *mijk, int ei, int ej, int ek, int *&qu_e);

    void add_list_memory(int *&qu_s, int *&qu_e);

    inline void reset_mask() {
        for (unsigned int *mp(mask); mp < mask + hxyz; mp++) *mp = 0;
    }
};

class BASE {
public:
    const int nx, ny, nz, nxy, nxyz;
    const LD boxx, boxy, boxz, xsp, ysp, zsp;
    LD *mrad;
    static const unsigned int wl[wl_seq_length * wl_hgridcu];

    BASE(int nx_, int ny_, int nz_, LD boxx_, LD boxy_, LD boxz_);

    ~BASE() {
        delete[] mrad;
    }

protected:
    static inline int step_int(LD a) {
        return a < 0 ? int(a) - 1 : int(a);
    }

private:
    void compute_minimum(LD &minr, LD &xlo, LD &xhi, LD &ylo, LD &yhi, LD &zlo, LD &zhi, int ti, int tj, int tk) const;
};

class CELLBASE {
public:
    int current_vertices, current_vertex_order, current_delete_size, current_delete2_size, current_xsearch_size, p, up, **ed, *nu;
    unsigned int *mask;
    LD *pts, tol, big_tol;

    explicit CELLBASE(LD max_len_sq);

    ~CELLBASE();

    void init_base(LD xmin, LD xmax, LD ymin, LD ymax, LD zmin, LD zmax);

    LD volume();

    LD max_radius_squared() const;

    template<class C>
    bool nplane(C &vc, LD x, LD y, LD z, LD rsq, int p_id);

    bool plane_intersects(LD x, LD y, LD z, LD rsq);

    bool plane_intersects_guess(LD x, LD y, LD z, LD rsq);

    inline int cycle_up(int a, int b) const {
        return a == nu[b] - 1 ? 0 : a + 1;
    }

    inline int cycle_down(int a, int b) const {
        return a == 0 ? nu[b] - 1 : a - 1;
    }

protected:
    int *mem, *mec, **mep;

    inline void reset_edges() const;

    template<class C>
    void check_memory_for_copy(C &vc, CELLBASE *vb);

    void copy(CELLBASE *vb);

private:
    int *ds, *stackp, *stacke, *ds2, *stackp2, *stacke2, *xse, *stackp3, *stacke3;
    unsigned int maskc;
    LD px, py, pz, prsq;

    template<class C>
    void add_memory(C &vc, int i);

    template<class C>
    void add_memory_vertices(C &vc);

    template<class C>
    void add_memory_vorder(C &vc);

    void add_memory_ds();

    void add_memory_ds2();

    void add_memory_xse();

    template<class C>
    bool create_facet(C &vc, int lp, int ls, LD l, int us, LD u, int p_id);

    template<class C>
    bool collapse_order1(C &vc);

    template<class C>
    inline bool collapse_order2(C &vc);

    template<class C>
    bool delete_connection(C &vc, int j, int k, bool hand);

    inline bool search_for_outside_edge(int &up);

    inline void add_to_stack(int sc2, int lp);

    inline void reset_mask() {
        for (int i = 0; i < current_vertices; i++) mask[i] = 0;
        maskc = 4;
    }

    inline bool search_downward(unsigned int &lw, int &lp, int &ls, int &us, LD &l, LD &u);

    bool definite_max(int &lp, int &ls, LD &l, LD &u, unsigned int &uw);

    inline bool search_upward(unsigned int &uw, int &lp, int &ls, int &us, LD &l, LD &u);

    bool definite_min(int &lp, int &us, LD &l, LD &u, unsigned int &lw);

    inline bool plane_intersects_track(LD x, LD y, LD z, LD rs, LD g) const;

    inline unsigned int m_test(int n, LD &ans);

    inline unsigned int m_testx(int n, LD &ans);

    unsigned int m_calc(int n, LD &ans) const;

    inline void flip(int tp) const {
        ed[tp][nu[tp] << 1] = -1 - ed[tp][nu[tp] << 1];
    }

    friend class CELL;

    friend class CELLNEIGHBOR;
};

class CELL : public CELLBASE {
public:
    CELL() : CELLBASE(default_length * default_length) {}

    template<class T>
    explicit CELL(T &con) : CELLBASE(con.max_len_sq) {}

    inline void operator=(CELL &c) {
        auto *vb((CELLBASE *) &c);
        check_memory_for_copy(*this, vb);
        copy(vb);
    }

    inline bool nplane(LD x, LD y, LD z, LD rsq, int p_id) {
        return CELLBASE::nplane(*this, x, y, z, rsq, 0);
    }

    inline void init(LD xmin, LD xmax, LD ymin, LD ymax, LD zmin, LD zmax) {
        init_base(xmin, xmax, ymin, ymax, zmin, zmax);
    }

private:
    inline void n_allocate(int i, int m) {};

    inline void n_add_memory_vertices(int i) {};

    inline void n_add_memory_vorder(int i) {};

    inline void n_set_pointer(int p, int n) {};

    inline void n_copy(int a, int b, int c, int d) {};

    inline void n_set(int a, int b, int c) {};

    inline void n_set_aux1(int k) {};

    inline void n_copy_aux1(int a, int b) {};

    inline void n_copy_aux1_shift(int a, int b) {};

    inline void n_set_aux2_copy(int a, int b) {};

    inline void n_copy_pointer(int a, int b) {};

    inline void n_set_to_aux1(int j) {};

    inline void n_allocate_aux1(int i) {};

    inline void n_switch_to_aux1(int i) {};

    inline void n_copy_to_aux1(int i, int m) {};

    inline void n_set_to_aux1_offset(int k, int m) {};

    friend class CELLBASE;
};

class CELLNEIGHBOR : public CELLBASE {
public:
    int **mne, **ne;

    CELLNEIGHBOR() : CELLBASE(default_length * default_length) {
        memory_setup();
    }

    ~CELLNEIGHBOR();

    void operator=(CELL &c);

    void operator=(CELLNEIGHBOR &c);

    inline bool nplane(LD x, LD y, LD z, LD rsq, int p_id) {
        return CELLBASE::nplane(*this, x, y, z, rsq, p_id);
    }

    void init(LD xmin, LD xmax, LD ymin, LD ymax, LD zmin, LD zmax);

private:
    int *paux1, *paux2;

    void memory_setup();

    inline void n_allocate(int i, int m) const {
        mne[i] = new int[m * i];
    }

    inline void n_add_memory_vertices(int i) {
        int **pp = new int *[i];
        for (int j = 0; j < current_vertices; j++) pp[j] = ne[j];
        delete[] ne;
        ne = pp;
    }

    inline void n_add_memory_vorder(int i) {
        int **p2 = new int *[i];
        for (int j = 0; j < current_vertex_order; j++) p2[j] = mne[j];
        delete[] mne;
        mne = p2;
    }

    inline void n_set_pointer(int p, int n) {
        ne[p] = mne[n] + n * mec[n];
    }

    inline void n_copy(int a, int b, int c, int d) const {
        ne[a][b] = ne[c][d];
    }

    inline void n_set(int a, int b, int c) const {
        ne[a][b] = c;
    }

    inline void n_set_aux1(int k) {
        paux1 = mne[k] + k * mec[k];
    }

    inline void n_copy_aux1(int a, int b) {
        paux1[b] = ne[a][b];
    }

    inline void n_copy_aux1_shift(int a, int b) {
        paux1[b] = ne[a][b + 1];
    }

    inline void n_set_aux2_copy(int a, int b) {
        paux2 = mne[b] + b * mec[b];
        for (int i = 0; i < b; i++) ne[a][i] = paux2[i];
    }

    inline void n_copy_pointer(int a, int b) const {
        ne[a] = ne[b];
    }

    inline void n_set_to_aux1(int j) {
        ne[j] = paux1;
    }

    inline void n_allocate_aux1(int i) {
        paux1 = new int[i * mem[i]];
    }

    inline void n_switch_to_aux1(int i) {
        delete[] mne[i];
        mne[i] = paux1;
    }

    inline void n_copy_to_aux1(int i, int m) {
        paux1[m] = mne[i][m];
    }

    inline void n_set_to_aux1_offset(int k, int m) {
        ne[k] = paux1 + m;
    }

    friend class CELLBASE;
};

class LOOPBASE {
public:
    const int nx, ny, nz, nxy, nxyz, ps;
    LD **p;
    int **id, *co, i, j, k, ijk, q;

    template<class T>
    explicit LOOPBASE(T &con) : nx(con.nx), ny(con.ny), nz(con.nz), nxy(con.nxy), nxyz(con.nxyz), ps(con.ps), p(con.p), id(con.id), co(con.co) {}
};

class LOOP : public LOOPBASE {
public:
    template<class T>
    explicit LOOP(T &con) : LOOPBASE(con) {}

    inline bool start() {
        i = j = k = ijk = q = 0;
        while (co[ijk] == 0) if (!next_block()) return false;
        return true;
    }

    inline bool inc() {
        q++;
        if (q >= co[ijk]) {
            q = 0;
            do if (!next_block()) return false; while (co[ijk] == 0);
        }
        return true;
    }

private:
    inline bool next_block() {
        ijk++;
        i++;
        if (i == nx) {
            i = 0;
            j++;
            if (j == ny) {
                j = 0;
                k++;
                if (ijk == nxyz) return false;
            }
        }
        return true;
    }
};

class RADIUS {
protected:
    inline void r_init(int ijk, int s) {}

    inline void r_prime(LD rv) {}

    static inline bool r_ctest(LD crs, LD mrs) {
        return crs > mrs;
    }

    static inline LD r_cutoff(LD lrs) {
        return lrs;
    }

    static inline LD r_scale(LD rs, int ijk, int q) {
        return rs;
    }

    static inline bool r_scale_check(LD &rs, LD mrs, int ijk, int q) {
        return rs < mrs;
    }
};

class WALL {
public:
    virtual~WALL() = default;

    virtual bool cut_cell(CELL &c, LD x, LD y, LD z) = 0;

    virtual bool cut_cell(CELLNEIGHBOR &c, LD x, LD y, LD z) = 0;
};

class WALLS {
public:
    WALL **walls, **wep;

    WALLS();

    ~WALLS();

    template<class T>
    bool apply_walls(T &c, LD x, LD y, LD z) {
        for (WALL **wp = walls; wp < wep; wp++) if (!((*wp)->cut_cell(c, x, y, z))) return false;
        return true;
    }
};

class CONTAINERBASE : public BASE, public WALLS {
public:
    const LD ax, bx, ay, by, az, bz, max_len_sq;
    int **id, *co, *mem;
    LD **p;
    const int ps;

    CONTAINERBASE(LD ax_, LD bx_, LD ay_, LD by_, LD az_, LD bz_, int nx_, int ny_, int nz_, int init_mem, int ps_);

    ~CONTAINERBASE();

    template<class V>
    inline bool initialize_voronoicell(V &c, int ijk, int q, int ci, int cj, int ck, int &i, int &j, int &k, LD &x, LD &y, LD &z, int &disp) {
        LD x1, x2, y1, y2, z1, z2, *pp = p[ijk] + ps * q;
        x = *(pp++);
        y = *(pp++);
        z = *pp;
        x1 = ax - x;
        x2 = bx - x;
        i = ci;
        y1 = ay - y;
        y2 = by - y;
        j = cj;
        z1 = az - z;
        z2 = bz - z;
        k = ck;
        c.init(x1, x2, y1, y2, z1, z2);
        if (!apply_walls(c, x, y, z)) return false;
        disp = ijk - i - nx * (j + ny * k);
        return true;
    }

    inline void frac_pos(LD x, LD y, LD z, LD ci, LD cj, LD ck, LD &fx, LD &fy, LD &fz) {
        fx = x - ax - boxx * ci;
        fy = y - ay - boxy * cj;
        fz = z - az - boxz * ck;
    }

    inline int region_index(int ci, int cj, int ck, int ei, int ej, int ek, LD &qx, LD &qy, LD &qz, int &disp) {
        return disp + ei + nx * (ej + ny * ek);
    }

protected:
    void add_particle_memory(int i) const;

    bool put_locate_block(int &ijk, LD &x, LD &y, LD &z);

    inline bool put_remap(int &ijk, LD &x, LD &y, LD &z);
};

class CONTAINER : public CONTAINERBASE, public RADIUS {
public:
    CONTAINER(LD ax_, LD bx_, LD ay_, LD by_, LD az_, LD bz_, int nx_, int ny_, int nz_, int init_mem);

    void put(int n, LD x, LD y, LD z);

    vector<LD> cell_volumes(int particles);

    template<class V, class c_loop>
    inline bool compute_cell(V &c, c_loop &vl) {
        return vc.compute_cell(c, vl.ijk, vl.q, vl.i, vl.j, vl.k);
    }

private:
    COMPUTER<CONTAINER> vc;

    friend class COMPUTER<CONTAINER>;
};

template<class T>
COMPUTER<T>::COMPUTER(T &con_, int hx_, int hy_, int hz_) :
        con(con_), boxx(con_.boxx), boxy(con_.boxy), boxz(con_.boxz), xsp(con_.xsp), ysp(con_.ysp), zsp(con_.zsp), hx(hx_), hy(hy_), hz(hz_), hxy(hx_ * hy_), hxyz(hxy * hz_), ps(con_.ps),
        id(con_.id), p(con_.p), co(con_.co), bxsq(boxx * boxx + boxy * boxy + boxz * boxz), mv(0), qu_size(3 * (3 + hxy + hz * (hx + hy))), wl(con_.wl), mrad(con_.mrad),
        mask(new unsigned int[hxyz]), qu(new int[qu_size]), qu_l(qu + qu_size) {
    reset_mask();
}

template<class T>
inline void COMPUTER<T>::add_to_mask(int ei, int ej, int ek, int *&qu_e) {
    unsigned int *mijk = mask + ei + hx * (ej + hy * ek);
    if (ek > 0)
        if (*(mijk - hxy) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk - hxy) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej;
            *(qu_e++) = ek - 1;
        }
    if (ej > 0)
        if (*(mijk - hx) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk - hx) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej - 1;
            *(qu_e++) = ek;
        }
    if (ei > 0)
        if (*(mijk - 1) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk - 1) = mv;
            *(qu_e++) = ei - 1;
            *(qu_e++) = ej;
            *(qu_e++) = ek;
        }
    if (ei < hx - 1)
        if (*(mijk + 1) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk + 1) = mv;
            *(qu_e++) = ei + 1;
            *(qu_e++) = ej;
            *(qu_e++) = ek;
        }
    if (ej < hy - 1)
        if (*(mijk + hx) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk + hx) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej + 1;
            *(qu_e++) = ek;
        }
    if (ek < hz - 1)
        if (*(mijk + hxy) != mv) {
            if (qu_e == qu_l) qu_e = qu;
            *(mijk + hxy) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej;
            *(qu_e++) = ek + 1;
        }
}

template<class T>
inline void COMPUTER<T>::scan_bits_mask_add(unsigned int q, unsigned int *mijk, int ei, int ej, int ek, int *&qu_e) {
    const unsigned int b1 = 1 << 21, b2 = 1 << 22, b3 = 1 << 24, b4 = 1 << 25, b5 = 1 << 27, b6 = 1 << 28;
    if ((q & b2) == b2) {
        if (ei > 0) {
            *(mijk - 1) = mv;
            *(qu_e++) = ei - 1;
            *(qu_e++) = ej;
            *(qu_e++) = ek;
        }
        if ((q & b1) == 0 && ei < hx - 1) {
            *(mijk + 1) = mv;
            *(qu_e++) = ei + 1;
            *(qu_e++) = ej;
            *(qu_e++) = ek;
        }
    } else if ((q & b1) == b1 && ei < hx - 1) {
        *(mijk + 1) = mv;
        *(qu_e++) = ei + 1;
        *(qu_e++) = ej;
        *(qu_e++) = ek;
    }
    if ((q & b4) == b4) {
        if (ej > 0) {
            *(mijk - hx) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej - 1;
            *(qu_e++) = ek;
        }
        if ((q & b3) == 0 && ej < hy - 1) {
            *(mijk + hx) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej + 1;
            *(qu_e++) = ek;
        }
    } else if ((q & b3) == b3 && ej < hy - 1) {
        *(mijk + hx) = mv;
        *(qu_e++) = ei;
        *(qu_e++) = ej + 1;
        *(qu_e++) = ek;
    }
    if ((q & b6) == b6) {
        if (ek > 0) {
            *(mijk - hxy) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej;
            *(qu_e++) = ek - 1;
        }
        if ((q & b5) == 0 && ek < hz - 1) {
            *(mijk + hxy) = mv;
            *(qu_e++) = ei;
            *(qu_e++) = ej;
            *(qu_e++) = ek + 1;
        }
    } else if ((q & b5) == b5 && ek < hz - 1) {
        *(mijk + hxy) = mv;
        *(qu_e++) = ei;
        *(qu_e++) = ej;
        *(qu_e++) = ek + 1;
    }
}

template<class T>
template<class V>
bool COMPUTER<T>::compute_cell(V &c, int ijk, int s, int ci, int cj, int ck) {
    static const int count_list[8] = {7, 11, 15, 19, 26, 35, 45, 59}, *count_e = count_list + 8;
    LD x, y, z, x1, y1, z1, qx = 0, qy = 0, qz = 0, xlo, ylo, zlo, xhi, yhi, zhi, x2, y2, z2, rs, fx, fy, fz, gxs, gys, gzs, *radp;
    int i, j, k, di, dj, dk, ei, ej, ek, f, g, l, disp;
    unsigned int q, *e, *mijk, m1, m2;
    if (!con.initialize_voronoicell(c, ijk, s, ci, cj, ck, i, j, k, x, y, z, disp)) return false;
    con.r_init(ijk, s);
    LD crs, mrs;
    int next_count = 3, *count_p = (const_cast <int *> (count_list));
    for (l = 0; l < s; l++) {
        x1 = p[ijk][ps * l] - x;
        y1 = p[ijk][ps * l + 1] - y;
        z1 = p[ijk][ps * l + 2] - z;
        rs = con.r_scale(x1 * x1 + y1 * y1 + z1 * z1, ijk, l);
        if (!c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
    }
    l++;
    while (l < co[ijk]) {
        x1 = p[ijk][ps * l] - x;
        y1 = p[ijk][ps * l + 1] - y;
        z1 = p[ijk][ps * l + 2] - z;
        rs = con.r_scale(x1 * x1 + y1 * y1 + z1 * z1, ijk, l);
        if (!c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
        l++;
    }
    mrs = c.max_radius_squared();
    con.frac_pos(x, y, z, ci, cj, ck, fx, fy, fz);
    di = int(fx * xsp * wl_fgrid);
    dj = int(fy * ysp * wl_fgrid);
    dk = int(fz * zsp * wl_fgrid);
    if (di >= wl_hgrid) {
        gxs = fx;
        m1 = 127 + (3 << 21);
        m2 = 1 + (1 << 21);
        di = wl_fgrid - 1 - di;
        if (di < 0) di = 0;
    } else {
        m1 = m2 = 0;
        gxs = boxx - fx;
    }
    if (dj >= wl_hgrid) {
        gys = fy;
        m1 |= (127 << 7) + (3 << 24);
        m2 |= (1 << 7) + (1 << 24);
        dj = wl_fgrid - 1 - dj;
        if (dj < 0) dj = 0;
    } else gys = boxy - fy;
    if (dk >= wl_hgrid) {
        gzs = fz;
        m1 |= (127 << 14) + (3 << 27);
        m2 |= (1 << 14) + (1 << 27);
        dk = wl_fgrid - 1 - dk;
        if (dk < 0) dk = 0;
    } else gzs = boxz - fz;
    gxs *= gxs;
    gys *= gys;
    gzs *= gzs;
    ijk = di + wl_hgrid * (dj + wl_hgrid * dk);
    radp = mrad + ijk * wl_seq_length;
    e = (const_cast <unsigned int *> (wl)) + ijk * wl_seq_length;
    f = e[0];
    g = 0;
    do {
        if (g == next_count) {
            mrs = c.max_radius_squared();
            if (count_p != count_e) next_count = *(count_p++);
        }
        if (con.r_ctest(radp[g], mrs)) return true;
        g++;
        q = e[g];
        q ^= m1;
        q += m2;
        di = q & 127;
        di -= 64;
        dj = (q >> 7) & 127;
        dj -= 64;
        dk = (q >> 14) & 127;
        dk -= 64;
        ei = di + i;
        if (ei < 0 || ei >= hx) continue;
        ej = dj + j;
        if (ej < 0 || ej >= hy) continue;
        ek = dk + k;
        if (ek < 0 || ek >= hz) continue;
        if (compute_min_max_radius(di, dj, dk, fx, fy, fz, gxs, gys, gzs, crs, mrs)) continue;
        ijk = con.region_index(ci, cj, ck, ei, ej, ek, qx, qy, qz, disp);
        if (co[ijk] > 0) {
            l = 0;
            x2 = x - qx;
            y2 = y - qy;
            z2 = z - qz;
            if (!con.r_ctest(crs, mrs)) {
                do {
                    x1 = p[ijk][ps * l] - x2;
                    y1 = p[ijk][ps * l + 1] - y2;
                    z1 = p[ijk][ps * l + 2] - z2;
                    rs = con.r_scale(x1 * x1 + y1 * y1 + z1 * z1, ijk, l);
                    if (!c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
                    l++;
                } while (l < co[ijk]);
            } else {
                do {
                    x1 = p[ijk][ps * l] - x2;
                    y1 = p[ijk][ps * l + 1] - y2;
                    z1 = p[ijk][ps * l + 2] - z2;
                    rs = x1 * x1 + y1 * y1 + z1 * z1;
                    if (con.r_scale_check(rs, mrs, ijk, l) && !c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
                    l++;
                } while (l < co[ijk]);
            }
        }
    } while (g < f);
    mv++;
    if (mv == 0) {
        reset_mask();
        mv = 1;
    }
    int *qu_s = qu, *qu_e = qu;
    while (g < wl_seq_length - 1) {
        if (g == next_count) {
            mrs = c.max_radius_squared();
            if (count_p != count_e) next_count = *(count_p++);
        }
        if (con.r_ctest(radp[g], mrs)) return true;
        g++;
        q = e[g];
        q ^= m1;
        q += m2;
        di = q & 127;
        di -= 64;
        dj = (q >> 7) & 127;
        dj -= 64;
        dk = (q >> 14) & 127;
        dk -= 64;
        ei = di + i;
        if (ei < 0 || ei >= hx) continue;
        ej = dj + j;
        if (ej < 0 || ej >= hy) continue;
        ek = dk + k;
        if (ek < 0 || ek >= hz) continue;
        mijk = mask + ei + hx * (ej + hy * ek);
        *mijk = mv;
        if (compute_min_max_radius(di, dj, dk, fx, fy, fz, gxs, gys, gzs, crs, mrs)) continue;
        ijk = con.region_index(ci, cj, ck, ei, ej, ek, qx, qy, qz, disp);
        if (co[ijk] > 0) {
            l = 0;
            x2 = x - qx;
            y2 = y - qy;
            z2 = z - qz;
            if (!con.r_ctest(crs, mrs)) {
                do {
                    x1 = p[ijk][ps * l] - x2;
                    y1 = p[ijk][ps * l + 1] - y2;
                    z1 = p[ijk][ps * l + 2] - z2;
                    rs = con.r_scale(x1 * x1 + y1 * y1 + z1 * z1, ijk, l);
                    if (!c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
                    l++;
                } while (l < co[ijk]);
            } else {
                do {
                    x1 = p[ijk][ps * l] - x2;
                    y1 = p[ijk][ps * l + 1] - y2;
                    z1 = p[ijk][ps * l + 2] - z2;
                    rs = x1 * x1 + y1 * y1 + z1 * z1;
                    if (con.r_scale_check(rs, mrs, ijk, l) && !c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
                    l++;
                } while (l < co[ijk]);
            }
        }
        if (qu_e > qu_l - 18) add_list_memory(qu_s, qu_e);
        scan_bits_mask_add(q, mijk, ei, ej, ek, qu_e);
    }
    if (con.r_ctest(radp[g], mrs)) return true;
    while (qu_s != qu_e) {
        if (qu_s == qu_l) qu_s = qu;
        ei = *(qu_s++);
        ej = *(qu_s++);
        ek = *(qu_s++);
        xlo = (ei - i) * boxx - fx;
        xhi = xlo + boxx;
        ylo = (ej - j) * boxy - fy;
        yhi = ylo + boxy;
        zlo = (ek - k) * boxz - fz;
        zhi = zlo + boxz;
        if (ei > i) {
            if (ej > j) {
                if (ek > k) {
                    if (corner_test(c, xlo, ylo, zlo, xhi, yhi, zhi)) continue;
                } else if (ek < k) {
                    if (corner_test(c, xlo, ylo, zhi, xhi, yhi, zlo)) continue;
                } else {
                    if (edge_z_test(c, xlo, ylo, zlo, xhi, yhi, zhi)) continue;
                }
            } else if (ej < j) {
                if (ek > k) {
                    if (corner_test(c, xlo, yhi, zlo, xhi, ylo, zhi)) continue;
                } else if (ek < k) {
                    if (corner_test(c, xlo, yhi, zhi, xhi, ylo, zlo)) continue;
                } else {
                    if (edge_z_test(c, xlo, yhi, zlo, xhi, ylo, zhi)) continue;
                }
            } else {
                if (ek > k) {
                    if (edge_y_test(c, xlo, ylo, zlo, xhi, yhi, zhi)) continue;
                } else if (ek < k) {
                    if (edge_y_test(c, xlo, ylo, zhi, xhi, yhi, zlo)) continue;
                } else {
                    if (face_x_test(c, xlo, ylo, zlo, yhi, zhi)) continue;
                }
            }
        } else if (ei < i) {
            if (ej > j) {
                if (ek > k) {
                    if (corner_test(c, xhi, ylo, zlo, xlo, yhi, zhi)) continue;
                } else if (ek < k) {
                    if (corner_test(c, xhi, ylo, zhi, xlo, yhi, zlo)) continue;
                } else {
                    if (edge_z_test(c, xhi, ylo, zlo, xlo, yhi, zhi)) continue;
                }
            } else if (ej < j) {
                if (ek > k) {
                    if (corner_test(c, xhi, yhi, zlo, xlo, ylo, zhi)) continue;
                } else if (ek < k) {
                    if (corner_test(c, xhi, yhi, zhi, xlo, ylo, zlo)) continue;
                } else {
                    if (edge_z_test(c, xhi, yhi, zlo, xlo, ylo, zhi)) continue;
                }
            } else {
                if (ek > k) {
                    if (edge_y_test(c, xhi, ylo, zlo, xlo, yhi, zhi)) continue;
                } else if (ek < k) {
                    if (edge_y_test(c, xhi, ylo, zhi, xlo, yhi, zlo)) continue;
                } else {
                    if (face_x_test(c, xhi, ylo, zlo, yhi, zhi)) continue;
                }
            }
        } else {
            if (ej > j) {
                if (ek > k) {
                    if (edge_x_test(c, xlo, ylo, zlo, xhi, yhi, zhi)) continue;
                } else if (ek < k) {
                    if (edge_x_test(c, xlo, ylo, zhi, xhi, yhi, zlo)) continue;
                } else {
                    if (face_y_test(c, xlo, ylo, zlo, xhi, zhi)) continue;
                }
            } else if (ej < j) {
                if (ek > k) {
                    if (edge_x_test(c, xlo, yhi, zlo, xhi, ylo, zhi)) continue;
                } else if (ek < k) {
                    if (edge_x_test(c, xlo, yhi, zhi, xhi, ylo, zlo)) continue;
                } else {
                    if (face_y_test(c, xlo, yhi, zlo, xhi, zhi)) continue;
                }
            } else {
                if (ek > k) {
                    if (face_z_test(c, xlo, ylo, zlo, xhi, yhi)) continue;
                } else if (ek < k) {
                    if (face_z_test(c, xlo, ylo, zhi, xhi, yhi)) continue;
                }
            }
        }
        ijk = con.region_index(ci, cj, ck, ei, ej, ek, qx, qy, qz, disp);
        if (co[ijk] > 0) {
            l = 0;
            x2 = x - qx;
            y2 = y - qy;
            z2 = z - qz;
            do {
                x1 = p[ijk][ps * l] - x2;
                y1 = p[ijk][ps * l + 1] - y2;
                z1 = p[ijk][ps * l + 2] - z2;
                rs = con.r_scale(x1 * x1 + y1 * y1 + z1 * z1, ijk, l);
                if (!c.nplane(x1, y1, z1, rs, id[ijk][l])) return false;
                l++;
            } while (l < co[ijk]);
        }
        if ((qu_s <= qu_e ? (qu_l - qu_e) + (qu_s - qu) : qu_s - qu_e) < 18) add_list_memory(qu_s, qu_e);
        add_to_mask(ei, ej, ek, qu_e);
    }
    return true;
}

template<class T>
template<class V>
bool COMPUTER<T>::corner_test(V &c, LD xl, LD yl, LD zl, LD xh, LD yh, LD zh) {
    con.r_prime(xl * xl + yl * yl + zl * zl);
    if (c.plane_intersects_guess(xh, yl, zl, con.r_cutoff(xl * xh + yl * yl + zl * zl))) return false;
    if (c.plane_intersects(xh, yh, zl, con.r_cutoff(xl * xh + yl * yh + zl * zl))) return false;
    if (c.plane_intersects(xl, yh, zl, con.r_cutoff(xl * xl + yl * yh + zl * zl))) return false;
    if (c.plane_intersects(xl, yh, zh, con.r_cutoff(xl * xl + yl * yh + zl * zh))) return false;
    if (c.plane_intersects(xl, yl, zh, con.r_cutoff(xl * xl + yl * yl + zl * zh))) return false;
    if (c.plane_intersects(xh, yl, zh, con.r_cutoff(xl * xh + yl * yl + zl * zh))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::edge_x_test(V &c, LD x0, LD yl, LD zl, LD x1, LD yh, LD zh) {
    con.r_prime(yl * yl + zl * zl);
    if (c.plane_intersects_guess(x0, yl, zh, con.r_cutoff(yl * yl + zl * zh))) return false;
    if (c.plane_intersects(x1, yl, zh, con.r_cutoff(yl * yl + zl * zh))) return false;
    if (c.plane_intersects(x1, yl, zl, con.r_cutoff(yl * yl + zl * zl))) return false;
    if (c.plane_intersects(x0, yl, zl, con.r_cutoff(yl * yl + zl * zl))) return false;
    if (c.plane_intersects(x0, yh, zl, con.r_cutoff(yl * yh + zl * zl))) return false;
    if (c.plane_intersects(x1, yh, zl, con.r_cutoff(yl * yh + zl * zl))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::edge_y_test(V &c, LD xl, LD y0, LD zl, LD xh, LD y1, LD zh) {
    con.r_prime(xl * xl + zl * zl);
    if (c.plane_intersects_guess(xl, y0, zh, con.r_cutoff(xl * xl + zl * zh))) return false;
    if (c.plane_intersects(xl, y1, zh, con.r_cutoff(xl * xl + zl * zh))) return false;
    if (c.plane_intersects(xl, y1, zl, con.r_cutoff(xl * xl + zl * zl))) return false;
    if (c.plane_intersects(xl, y0, zl, con.r_cutoff(xl * xl + zl * zl))) return false;
    if (c.plane_intersects(xh, y0, zl, con.r_cutoff(xl * xh + zl * zl))) return false;
    if (c.plane_intersects(xh, y1, zl, con.r_cutoff(xl * xh + zl * zl))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::edge_z_test(V &c, LD xl, LD yl, LD z0, LD xh, LD yh, LD z1) {
    con.r_prime(xl * xl + yl * yl);
    if (c.plane_intersects_guess(xl, yh, z0, con.r_cutoff(xl * xl + yl * yh))) return false;
    if (c.plane_intersects(xl, yh, z1, con.r_cutoff(xl * xl + yl * yh))) return false;
    if (c.plane_intersects(xl, yl, z1, con.r_cutoff(xl * xl + yl * yl))) return false;
    if (c.plane_intersects(xl, yl, z0, con.r_cutoff(xl * xl + yl * yl))) return false;
    if (c.plane_intersects(xh, yl, z0, con.r_cutoff(xl * xh + yl * yl))) return false;
    if (c.plane_intersects(xh, yl, z1, con.r_cutoff(xl * xh + yl * yl))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::face_x_test(V &c, LD xl, LD y0, LD z0, LD y1, LD z1) {
    con.r_prime(xl * xl);
    if (c.plane_intersects_guess(xl, y0, z0, con.r_cutoff(xl * xl))) return false;
    if (c.plane_intersects(xl, y0, z1, con.r_cutoff(xl * xl))) return false;
    if (c.plane_intersects(xl, y1, z1, con.r_cutoff(xl * xl))) return false;
    if (c.plane_intersects(xl, y1, z0, con.r_cutoff(xl * xl))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::face_y_test(V &c, LD x0, LD yl, LD z0, LD x1, LD z1) {
    con.r_prime(yl * yl);
    if (c.plane_intersects_guess(x0, yl, z0, con.r_cutoff(yl * yl))) return false;
    if (c.plane_intersects(x0, yl, z1, con.r_cutoff(yl * yl))) return false;
    if (c.plane_intersects(x1, yl, z1, con.r_cutoff(yl * yl))) return false;
    if (c.plane_intersects(x1, yl, z0, con.r_cutoff(yl * yl))) return false;
    return true;
}

template<class T>
template<class V>
inline bool COMPUTER<T>::face_z_test(V &c, LD x0, LD y0, LD zl, LD x1, LD y1) {
    con.r_prime(zl * zl);
    if (c.plane_intersects_guess(x0, y0, zl, con.r_cutoff(zl * zl))) return false;
    if (c.plane_intersects(x0, y1, zl, con.r_cutoff(zl * zl))) return false;
    if (c.plane_intersects(x1, y1, zl, con.r_cutoff(zl * zl))) return false;
    if (c.plane_intersects(x1, y0, zl, con.r_cutoff(zl * zl))) return false;
    return true;
}

template<class T>
bool COMPUTER<T>::compute_min_max_radius(int di, int dj, int dk, LD fx, LD fy, LD fz, LD gxs, LD gys, LD gzs, LD &crs, LD mrs) {
    LD xlo, ylo, zlo;
    if (di > 0) {
        xlo = di * boxx - fx;
        crs = xlo * xlo;
        if (dj > 0) {
            ylo = dj * boxy - fy;
            crs += ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (boxx * xlo + boxy * ylo + boxz * zlo);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (boxx * xlo + boxy * ylo - boxz * zlo);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxx * (2 * xlo + boxx) + boxy * (2 * ylo + boxy) + gzs;
            }
        } else if (dj < 0) {
            ylo = (dj + 1) * boxy - fy;
            crs += ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (boxx * xlo - boxy * ylo + boxz * zlo);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (boxx * xlo - boxy * ylo - boxz * zlo);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxx * (2 * xlo + boxx) + boxy * (-2 * ylo + boxy) + gzs;
            }
        } else {
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (2 * zlo + boxz);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (-2 * zlo + boxz);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += gzs;
            }
            crs += gys + boxx * (2 * xlo + boxx);
        }
    } else if (di < 0) {
        xlo = (di + 1) * boxx - fx;
        crs = xlo * xlo;
        if (dj > 0) {
            ylo = dj * boxy - fy;
            crs += ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (-boxx * xlo + boxy * ylo + boxz * zlo);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (-boxx * xlo + boxy * ylo - boxz * zlo);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxx * (-2 * xlo + boxx) + boxy * (2 * ylo + boxy) + gzs;
            }
        } else if (dj < 0) {
            ylo = (dj + 1) * boxy - fy;
            crs += ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (-boxx * xlo - boxy * ylo + boxz * zlo);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += bxsq + 2 * (-boxx * xlo - boxy * ylo - boxz * zlo);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxx * (-2 * xlo + boxx) + boxy * (-2 * ylo + boxy) + gzs;
            }
        } else {
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (2 * zlo + boxz);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (-2 * zlo + boxz);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += gzs;
            }
            crs += gys + boxx * (-2 * xlo + boxx);
        }
    } else {
        if (dj > 0) {
            ylo = dj * boxy - fy;
            crs = ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (2 * zlo + boxz);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (-2 * zlo + boxz);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += gzs;
            }
            crs += boxy * (2 * ylo + boxy);
        } else if (dj < 0) {
            ylo = (dj + 1) * boxy - fy;
            crs = ylo * ylo;
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (2 * zlo + boxz);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs += zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (-2 * zlo + boxz);
            } else {
                if (con.r_ctest(crs, mrs)) return true;
                crs += gzs;
            }
            crs += boxy * (-2 * ylo + boxy);
        } else {
            if (dk > 0) {
                zlo = dk * boxz - fz;
                crs = zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (2 * zlo + boxz);
            } else if (dk < 0) {
                zlo = (dk + 1) * boxz - fz;
                crs = zlo * zlo;
                if (con.r_ctest(crs, mrs)) return true;
                crs += boxz * (-2 * zlo + boxz);
            } else {
                crs = 0;
            }
            crs += gys;
        }
        crs += gxs;
    }
    return false;
}

template<class T>
inline void COMPUTER<T>::add_list_memory(int *&qu_s, int *&qu_e) {
    qu_size <<= 1;
    int *qu_n = new int[qu_size], *qu_c = qu_n;
    if (qu_s <= qu_e) {
        while (qu_s < qu_e) *(qu_c++) = *(qu_s++);
    } else {
        while (qu_s < qu_l) *(qu_c++) = *(qu_s++);
        qu_s = qu;
        while (qu_s < qu_e) *(qu_c++) = *(qu_s++);
    }
    delete[] qu;
    qu_s = qu = qu_n;
    qu_l = qu + qu_size;
    qu_e = qu_c;
}

template bool COMPUTER<CONTAINER>::compute_cell(CELL &, int, int, int, int, int);

template bool COMPUTER<CONTAINER>::compute_cell(CELLNEIGHBOR &, int, int, int, int, int);

BASE::BASE(int nx_, int ny_, int nz_, LD boxx_, LD boxy_, LD boxz_) :
        nx(nx_), ny(ny_), nz(nz_), nxy(nx_ * ny_), nxyz(nxy * nz_), boxx(boxx_), boxy(boxy_), boxz(boxz_), xsp(1 / boxx_), ysp(1 / boxy_), zsp(1 / boxz_), mrad(new LD[wl_hgridcu * wl_seq_length]) {
    const unsigned int b1 = 1 << 21, b2 = 1 << 22, b3 = 1 << 24, b4 = 1 << 25, b5 = 1 << 27, b6 = 1 << 28;
    const LD xstep = boxx / wl_fgrid, ystep = boxy / wl_fgrid, zstep = boxz / wl_fgrid;
    int i, j, k, lx, ly, lz, q;
    unsigned int f, *e = const_cast <unsigned int *> (wl);
    LD xlo, ylo, zlo, xhi, yhi, zhi, minr, *radp = mrad;
    for (zlo = 0, zhi = zstep, lz = 0; lz < wl_hgrid; zlo = zhi, zhi += zstep, lz++) {
        for (ylo = 0, yhi = ystep, ly = 0; ly < wl_hgrid; ylo = yhi, yhi += ystep, ly++) {
            for (xlo = 0, xhi = xstep, lx = 0; lx < wl_hgrid; xlo = xhi, xhi += xstep, lx++) {
                minr = large_number;
                for (q = e[0] + 1; q < wl_seq_length; q++) {
                    f = e[q];
                    i = (f & 127) - 64;
                    j = (f >> 7 & 127) - 64;
                    k = (f >> 14 & 127) - 64;
                    if ((f & b2) == b2) {
                        compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i - 1, j, k);
                        if ((f & b1) == 0) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i + 1, j, k);
                    } else if ((f & b1) == b1) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i + 1, j, k);
                    if ((f & b4) == b4) {
                        compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j - 1, k);
                        if ((f & b3) == 0) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j + 1, k);
                    } else if ((f & b3) == b3) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j + 1, k);
                    if ((f & b6) == b6) {
                        compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j, k - 1);
                        if ((f & b5) == 0) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j, k + 1);
                    } else if ((f & b5) == b5) compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j, k + 1);
                }
                q--;
                while (q > 0) {
                    radp[q] = minr;
                    f = e[q];
                    i = (f & 127) - 64;
                    j = (f >> 7 & 127) - 64;
                    k = (f >> 14 & 127) - 64;
                    compute_minimum(minr, xlo, xhi, ylo, yhi, zlo, zhi, i, j, k);
                    q--;
                }
                *radp = minr;
                e += wl_seq_length;
                radp += wl_seq_length;
            }
        }
    }
}

void BASE::compute_minimum(LD &minr, LD &xlo, LD &xhi, LD &ylo, LD &yhi, LD &zlo, LD &zhi, int ti, int tj, int tk) const {
    LD radsq, temp;
    if (ti > 0) {
        temp = boxx * ti - xhi;
        radsq = temp * temp;
    } else if (ti < 0) {
        temp = xlo - boxx * (1 + ti);
        radsq = temp * temp;
    } else radsq = 0;
    if (tj > 0) {
        temp = boxy * tj - yhi;
        radsq += temp * temp;
    } else if (tj < 0) {
        temp = ylo - boxy * (1 + tj);
        radsq += temp * temp;
    }
    if (tk > 0) {
        temp = boxz * tk - zhi;
        radsq += temp * temp;
    } else if (tk < 0) {
        temp = zlo - boxz * (1 + tk);
        radsq += temp * temp;
    }
    if (radsq < minr) minr = radsq;
}

const unsigned int BASE::wl[wl_seq_length * wl_hgridcu] = {
        7, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x10fe0bf, 0x11020bf, 0x11020c0, 0x10fe0c0, 0x2fe041, 0x302041, 0x301fc1, 0x2fdfc1, 0x8105fc0, 0x8106040, 0x810603f, 0x8105fbf, 0x701fbe, 0x70203e, 0x6fe03e, 0x6fdfbe,
        0x30fdf3f, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x12fe0c1, 0x13020c1, 0x91060c0, 0x91060bf, 0x8306041, 0x8305fc1, 0x3301f41, 0x32fdf41, 0x182f9fc1, 0x182fa041, 0x190fa0c0, 0x190fa0bf, 0x16fe0be,
        0x17020be, 0x870603e, 0x8705fbe, 0xb105f3f, 0xb105f40, 0x3701f3e, 0x36fdf3e, 0x186f9fbe, 0x186fa03e, 0x1b0f9f3f, 0x1b0f9f40, 0x93060c1, 0x192fa0c1, 0x97060be, 0xb305f41, 0x1b2f9f41, 0x196fa0be, 0xb705f3e, 0x1b6f9f3e,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0x10203f, 0x101fbf, 0xfe03f, 0xfdfbf, 0xfdfc1, 0x101fc1, 0x102041, 0xfe041, 0x10fe0c0, 0x11020c0, 0x8106040, 0x8105fc0, 0x8105fbf, 0x810603f, 0x11020bf, 0x10fe0bf, 0x180fa040, 0x180f9fc0, 0x30fdf40, 0x3101f40,
        0x3101f3f, 0x30fdf3f, 0x180f9fbf, 0x180fa03f, 0x6fe03e, 0x70203e, 0x701fbe, 0x6fdfbe, 0x8105fc1, 0x8106041, 0x11020c1, 0x10fe0c1, 0x180fa041, 0x180f9fc1, 0x30fdf41, 0x3101f41, 0x91060c0, 0x91060bf, 0x190fa0c0, 0x190fa0bf, 0xb105f40,
        0xb105f3f, 0x8705fbe, 0x870603e, 0x97020be, 0x16fe0be, 0x1b0f9f40, 0x1b0f9f3f, 0x36fdf3e, 0xb701f3e, 0x1b6f9fbe, 0x196fa03e, 0x93060c1, 0xb305f41, 0x192fa0c1, 0x1b2f9f41, 0x1b2fdfc2, 0xb301fc2, 0x9302042, 0x192fe042,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0xfdfbf, 0x101fbf, 0x10203f, 0xfe03f, 0xfe041, 0x102041, 0x101fc1, 0xfdfc1, 0x8105fc0, 0x8106040, 0x11020c0, 0x10fe0c0, 0x10fe0bf, 0x11020bf, 0x810603f, 0x8105fbf, 0x3101f40, 0x30fdf40, 0x180f9fc0, 0x180fa040,
        0x180fa03f, 0x180f9fbf, 0x30fdf3f, 0x3101f3f, 0x8105fc1, 0x8106041, 0x11020c1, 0x10fe0c1, 0x180fa041, 0x180f9fc1, 0x30fdf41, 0x3101f41, 0x701fbe, 0x70203e, 0x6fe03e, 0x6fdfbe, 0x91060c0, 0x91060bf, 0xb105f40, 0xb105f3f, 0x190fa0c0,
        0x190fa0bf, 0x93060c1, 0x1b0f9f40, 0x1b0f9f3f, 0xb305f41, 0x192fa0c1, 0x16fe0be, 0x17020be, 0x970603e, 0x8705fbe, 0xb701f3e, 0x36fdf3e, 0x1b2f9f41, 0x1b2fdfc2, 0x192fe042, 0x9302042, 0xb301fc2, 0x1b6f9fbe, 0x196fa03e,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0xfdfbf, 0x101fbf, 0x10203f, 0xfe03f, 0xfe041, 0x102041, 0x101fc1, 0xfdfc1, 0x8105fc0, 0x8106040, 0x11020c0, 0x10fe0c0, 0x10fe0bf, 0x11020bf, 0x810603f, 0x8105fbf, 0x3101f40, 0x30fdf40, 0x180f9fc0, 0x180fa040,
        0x10fe0c1, 0x11020c1, 0x8106041, 0x8105fc1, 0x3101f3f, 0x30fdf3f, 0x180f9fbf, 0x180fa03f, 0x180fa041, 0x180f9fc1, 0x30fdf41, 0x3101f41, 0x91060c0, 0x91060bf, 0x70203e, 0x701fbe, 0x6fdfbe, 0x6fe03e, 0x190fa0c0, 0xb105f40, 0xb105f3f, 0x93060c1,
        0x190fa0bf, 0x192fa0c1, 0x1b0f9f40, 0x1b0f9f3f, 0xb305f41, 0xb301fc2, 0x9302042, 0x192fe042, 0x1b2fdfc2, 0x1b2f9f41, 0x16fe0be, 0x17020be, 0x970603e, 0x8705fbe, 0xb701f3e, 0x36fdf3e, 0x1b6f9fbe, 0x196fa03e,
        11, 0x10203f, 0xfe040, 0xfe03f, 0x101fc0, 0x101fbf, 0xfdfc0, 0xfdfbf, 0xfe0bf, 0x1020bf, 0x1020c0, 0xfe0c0, 0x2fe041, 0x302041, 0x8106040, 0x810603f, 0x8105fbf, 0x8105fc0, 0x301fc1, 0x2fdfc1, 0x180fa040, 0x180fa03f, 0x6fe03e, 0x70203e,
        0x701fbe, 0x6fdfbe, 0x180f9fbf, 0x180f9fc0, 0x30fdf40, 0x3101f40, 0x3101f3f, 0x30fdf3f, 0x81060bf, 0x81060c0, 0x3020c1, 0x2fe0c1, 0x180fa0c0, 0x180fa0bf, 0x6fe0be, 0x7020be, 0x8306041, 0x8305fc1, 0x182fa041, 0x182f9fc1, 0x870603e, 0x8705fbe,
        0xb105f3f, 0xb105f40, 0xb301f41, 0x32fdf41, 0x186fa03e, 0x186f9fbe, 0x36fdf3e, 0xb701f3e, 0x1b6f9f3f, 0x1b2f9f40, 0x93060c1, 0x97060be, 0x192fa0c1, 0x196fa0be, 0x196fe13f, 0x970213f, 0x9302140, 0x192fe140,
        9, 0xfe040, 0x10203f, 0x101fc0, 0xfdfc0, 0xfe03f, 0xfdfbf, 0x101fbf, 0x102041, 0xfe041, 0x10fe0c0, 0x11020c0, 0x11020bf, 0x10fe0bf, 0xfdfc1, 0x101fc1, 0x8106040, 0x810603f, 0x8105fc0, 0x8105fbf, 0x180fa040, 0x180f9fc0, 0x180fa03f, 0x180f9fbf,
        0x10fe0c1, 0x11020c1, 0x70203e, 0x6fe03e, 0x6fdfbe, 0x701fbe, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x8106041, 0x91060c0, 0x91060bf, 0x8305fc1, 0x180fa041, 0x190fa0c0, 0x190fa0bf, 0x180f9fc1, 0x30fdf41, 0x3301f41, 0x17020be, 0x16fe0be,
        0x93060c1, 0x870603e, 0x8705fbe, 0xb105f3f, 0xb105f40, 0x192fa0c1, 0x1b0f9f40, 0x1b0f9f3f, 0x186f9fbe, 0x196fa03e, 0x1b6fdf3e, 0xb701f3e, 0x97060be, 0xb305f41, 0x1b2f9f41, 0x1b2fdfc2, 0x192fe042, 0xa302042,
        11, 0xfe040, 0x101fc0, 0xfdfc0, 0xfe03f, 0x10203f, 0x101fbf, 0xfdfbf, 0xfe041, 0x102041, 0x101fc1, 0xfdfc1, 0x10fe0c0, 0x11020c0, 0x11020bf, 0x10fe0bf, 0x8106040, 0x8105fc0, 0x810603f, 0x8105fbf, 0x11020c1, 0x10fe0c1, 0x180fa040, 0x180f9fc0,
        0x180fa03f, 0x180f9fbf, 0x30fdf40, 0x3101f40, 0x8106041, 0x8105fc1, 0x3101f3f, 0x30fdf3f, 0x91060c0, 0x91060bf, 0x180fa041, 0x180f9fc1, 0x6fe03e, 0x70203e, 0x701fbe, 0x6fdfbe, 0x190fa0c0, 0x190fa0bf, 0x30fdf41, 0x3101f41, 0x93060c1,
        0x192fa0c1, 0xb105f40, 0xb105f3f, 0x17020be, 0x16fe0be, 0x970603e, 0x8705fbe, 0x1b0f9f40, 0x1b0f9f3f, 0x186f9fbe, 0x196fa03e, 0xb305f41, 0xb301fc2, 0x9302042, 0x192fe042, 0x1b2fdfc2, 0x1b2f9f41, 0x1b6fdf3e, 0xb701f3e,
        11, 0xfe040, 0x101fc0, 0xfdfc0, 0xfe03f, 0x10203f, 0x101fbf, 0xfdfbf, 0xfe041, 0x102041, 0x101fc1, 0xfdfc1, 0x10fe0c0, 0x11020c0, 0x11020bf, 0x10fe0bf, 0x8106040, 0x8105fc0, 0x11020c1, 0x10fe0c1, 0x810603f, 0x8105fbf, 0x180fa040, 0x180f9fc0,
        0x8106041, 0x8105fc1, 0x3101f40, 0x180fa03f, 0x180f9fbf, 0x30fdf40, 0x180fa041, 0x180f9fc1, 0x91060c0, 0x3101f3f, 0x30fdf3f, 0x30fdf41, 0x3101f41, 0x91060bf, 0x190fa0c0, 0x91060c1, 0x190fa0bf, 0x186fe03e, 0x70203e, 0x3701fbe, 0x1b6fdfbe,
        0x190fa0c1, 0x182fe042, 0xb105f40, 0xb105f3f, 0x302042, 0x3301fc2, 0x1b2fdfc2, 0x1b0f9f40, 0x1b6f9f3f, 0xb105f41, 0x17020be, 0x196fe0be, 0x970603e, 0xb705fbe, 0x1b2f9f41, 0x192fe0c2, 0x13020c2, 0x9306042, 0xb305fc2,
        11, 0x10203f, 0xfe040, 0xfe03f, 0xfdfbf, 0x101fbf, 0x101fc0, 0xfdfc0, 0xfe0c0, 0x1020c0, 0x1020bf, 0xfe0bf, 0x810603f, 0x8106040, 0x302041, 0x2fe041, 0x2fdfc1, 0x301fc1, 0x8105fc0, 0x8105fbf, 0x70203e, 0x6fe03e, 0x180fa03f, 0x180fa040,
        0x180f9fc0, 0x180f9fbf, 0x6fdfbe, 0x701fbe, 0x81060bf, 0x81060c0, 0x3020c1, 0x2fe0c1, 0x180fa0c0, 0x180fa0bf, 0x6fe0be, 0x7020be, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x8306041, 0x8305fc1, 0x870603e, 0x8705fbe, 0x182fa041, 0x182f9fc1,
        0x93060c1, 0x186fa03e, 0x186f9fbe, 0x97060be, 0x192fa0c1, 0x32fdf41, 0x3301f41, 0xb305f40, 0xb105f3f, 0xb701f3e, 0x36fdf3e, 0x196fa0be, 0x196fe13f, 0x192fe140, 0x9302140, 0x970213f, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0xfe040, 0x10203f, 0xfe03f, 0xfdfc0, 0x101fc0, 0x101fbf, 0xfdfbf, 0xfe0c0, 0x1020c0, 0x1020bf, 0xfe0bf, 0x2fe041, 0x302041, 0x301fc1, 0x2fdfc1, 0x8106040, 0x810603f, 0x8105fc0, 0x8105fbf, 0x3020c1, 0x2fe0c1, 0x180fa040, 0x180fa03f,
        0x180f9fc0, 0x180f9fbf, 0x6fe03e, 0x70203e, 0x81060c0, 0x81060bf, 0x701fbe, 0x6fdfbe, 0x8306041, 0x8305fc1, 0x180fa0c0, 0x180fa0bf, 0x30fdf40, 0x3101f40, 0x3101f3f, 0x30fdf3f, 0x182fa041, 0x182f9fc1, 0x6fe0be, 0x7020be, 0x93060c1, 0x192fa0c1,
        0x870603e, 0x8705fbe, 0x3301f41, 0x32fdf41, 0xb305f40, 0xb105f3f, 0x186fa03e, 0x186f9fbe, 0x1b0f9f3f, 0x1b2f9f40, 0x97060be, 0x970213f, 0x9302140, 0x192fe140, 0x196fe13f, 0x196fa0be, 0x1b6fdf3e, 0xb701f3e,
        15, 0xfe040, 0xfe03f, 0x10203f, 0x101fc0, 0xfdfc0, 0xfdfbf, 0x101fbf, 0x102041, 0xfe041, 0xfe0c0, 0x1020c0, 0x1020bf, 0xfe0bf, 0xfdfc1, 0x101fc1, 0x8106040, 0x1020c1, 0xfe0c1, 0x810603f, 0x8105fc0, 0x8105fbf, 0x180fa040, 0x180fa03f,
        0x180f9fc0, 0x180f9fbf, 0x8106041, 0x81060c0, 0x81060bf, 0x8105fc1, 0x180fa041, 0x180fa0c0, 0x180fa0bf, 0x6fe03e, 0x70203e, 0x3101f40, 0x30fdf40, 0x180f9fc1, 0x30fdf3f, 0x3101f3f, 0x3701fbe, 0x36fdfbe, 0x93060c1, 0x192fa0c1, 0x6fe0be,
        0x7020be, 0x3101f41, 0x30fdf41, 0xb305f40, 0xb105f3f, 0x970603e, 0xb705fbe, 0x196fa03e, 0x186f9fbe, 0x1b2f9f40, 0x1b6f9f3f, 0x192fe042, 0x9302042, 0xb301fc2, 0x1b2fdfc2, 0x192fe140, 0x9302140, 0x970213f, 0x196fe13f,
        15, 0xfe040, 0xfdfc0, 0x101fc0, 0x10203f, 0xfe03f, 0xfdfbf, 0x101fbf, 0x102041, 0xfe041, 0xfdfc1, 0x101fc1, 0x1020c0, 0xfe0c0, 0xfe0bf, 0x1020bf, 0x1020c1, 0xfe0c1, 0x8106040, 0x8105fc0, 0x810603f, 0x8105fbf, 0x180fa040, 0x180f9fc0,
        0x8106041, 0x8105fc1, 0x81060c0, 0x180fa03f, 0x180f9fbf, 0x180fa041, 0x180f9fc1, 0x180fa0c0, 0x81060bf, 0x91060c1, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x180fa0bf, 0x190fa0c1, 0x3101f3f, 0x3101f41, 0x30fdf41, 0x186fe03e, 0x70203e, 0x3701fbe,
        0x1b6fdfbe, 0x186fe0be, 0x7020be, 0x8302042, 0x182fe042, 0x1b2fdfc2, 0xb301fc2, 0xb105f40, 0xb705f3f, 0xb305f41, 0x1b2f9f40, 0x1b6f9f3f, 0x192fe140, 0x9302140, 0x93020c2, 0x192fe0c2, 0x196fe13f, 0x970213f, 0xa70603e,
        11, 0x10203f, 0xfe040, 0xfe03f, 0xfdfbf, 0x101fbf, 0x101fc0, 0xfdfc0, 0xfe0c0, 0x1020c0, 0x1020bf, 0xfe0bf, 0x810603f, 0x8106040, 0x302041, 0x2fe041, 0x2fdfc1, 0x301fc1, 0x8105fc0, 0x8105fbf, 0x70203e, 0x6fe03e, 0x180fa03f, 0x180fa040,
        0x2fe0c1, 0x3020c1, 0x81060c0, 0x81060bf, 0x701fbe, 0x6fdfbe, 0x180f9fbf, 0x180f9fc0, 0x180fa0c0, 0x180fa0bf, 0x6fe0be, 0x7020be, 0x8306041, 0x8305fc1, 0x3101f40, 0x3101f3f, 0x30fdf3f, 0x30fdf40, 0x182fa041, 0x870603e, 0x8705fbe, 0x93060c1,
        0x182f9fc1, 0x192fa0c1, 0x186fa03e, 0x186f9fbe, 0x97060be, 0x970213f, 0x9302140, 0x192fe140, 0x196fe13f, 0x196fa0be, 0x32fdf41, 0x3301f41, 0xb305f40, 0xb105f3f, 0xb701f3e, 0x36fdf3e, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0xfe040, 0x10203f, 0xfe03f, 0xfdfc0, 0x101fc0, 0x101fbf, 0xfdfbf, 0xfe0c0, 0x1020c0, 0x1020bf, 0xfe0bf, 0x2fe041, 0x302041, 0x301fc1, 0x2fdfc1, 0x8106040, 0x810603f, 0x3020c1, 0x2fe0c1, 0x8105fc0, 0x8105fbf, 0x180fa040, 0x180fa03f,
        0x81060c0, 0x81060bf, 0x70203e, 0x180f9fc0, 0x180f9fbf, 0x6fe03e, 0x180fa0c0, 0x180fa0bf, 0x8306041, 0x701fbe, 0x6fdfbe, 0x6fe0be, 0x7020be, 0x8305fc1, 0x182fa041, 0x83060c1, 0x182f9fc1, 0x1b0fdf40, 0x3101f40, 0x3701f3f, 0x1b6fdf3f,
        0x182fa0c1, 0x190fe140, 0x870603e, 0x8705fbe, 0x1102140, 0x170213f, 0x196fe13f, 0x186fa03e, 0x1b6f9fbe, 0x87060be, 0x3301f41, 0x1b2fdf41, 0xb305f40, 0xb705f3f, 0x196fa0be, 0x192fe141, 0x1302141, 0x9306140, 0x970613f,
        15, 0xfe040, 0xfe03f, 0x10203f, 0x101fc0, 0xfdfc0, 0xfdfbf, 0x101fbf, 0x1020c0, 0xfe0c0, 0xfe0bf, 0x1020bf, 0x102041, 0xfe041, 0xfdfc1, 0x101fc1, 0x1020c1, 0xfe0c1, 0x8106040, 0x810603f, 0x8105fc0, 0x8105fbf, 0x180fa040, 0x180fa03f,
        0x81060c0, 0x81060bf, 0x8106041, 0x180f9fc0, 0x180f9fbf, 0x180fa0c0, 0x180fa0bf, 0x180fa041, 0x8105fc1, 0x83060c1, 0x70203e, 0x6fe03e, 0x6fdfbe, 0x180f9fc1, 0x182fa0c1, 0x701fbe, 0x7020be, 0x6fe0be, 0x1b0fdf40, 0x3101f40, 0x3701f3f,
        0x1b6fdf3f, 0x1b0fdf41, 0x3101f41, 0x9102140, 0x190fe140, 0x196fe13f, 0x970213f, 0x870603e, 0xb705fbe, 0x97060be, 0x196fa03e, 0x1b6f9fbe, 0x192fe042, 0x9302042, 0x9302141, 0x192fe141, 0x1b2fdfc2, 0xb301fc2, 0xb505f40,
        17, 0xfe040, 0xfe03f, 0x10203f, 0x101fc0, 0xfdfc0, 0xfe041, 0x102041, 0x1020c0, 0xfe0c0, 0xfdfbf, 0x101fbf, 0x1020bf, 0xfe0bf, 0xfdfc1, 0x101fc1, 0x1020c1, 0xfe0c1, 0x8106040, 0x810603f, 0x8105fc0, 0x8106041, 0x81060c0, 0x180fa040,
        0x180fa03f, 0x180f9fc0, 0x8105fbf, 0x81060bf, 0x8105fc1, 0x180fa041, 0x180fa0c0, 0x180f9fbf, 0x81060c1, 0x180fa0bf, 0x180f9fc1, 0x180fa0c1, 0x186fe03e, 0x70203e, 0x3101f40, 0x1b0fdf40, 0x1b0fdf3f, 0x3101f3f, 0x3701fbe, 0x1b6fdfbe, 0x186fe0be,
        0x7020be, 0x9102140, 0x190fe140, 0x182fe042, 0x8302042, 0x3101f41, 0x1b0fdf41, 0x1b2fdfc2, 0xb301fc2, 0x83020c2, 0x182fe0c2, 0x196fe13f, 0x970213f, 0x9302141, 0x192fe141, 0x970603e, 0xb305f40, 0xb105f3f, 0xb705fbe,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfe040, 0xfe03f, 0xfdfc0, 0xfdfbf, 0x105fbf, 0x10603f, 0x106040, 0x105fc0, 0x301fc1, 0x302041, 0x11020c0, 0x11020bf, 0x10fe0bf, 0x10fe0c0, 0x2fe041, 0x2fdfc1, 0x3101f40, 0x3101f3f, 0x701fbe, 0x70203e,
        0x6fe03e, 0x6fdfbe, 0x30fdf3f, 0x30fdf40, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x11060bf, 0x11060c0, 0x306041, 0x305fc1, 0x3105f40, 0x3105f3f, 0x705fbe, 0x70603e, 0x13020c1, 0x12fe0c1, 0x3301f41, 0x32fdf41, 0x17020be, 0x16fe0be,
        0x190fa0bf, 0x190fa0c0, 0x192fa041, 0x182f9fc1, 0x3701f3e, 0x36fdf3e, 0x186f9fbe, 0x196fa03e, 0x1b6f9f3f, 0x1b2f9f40, 0x93060c1, 0x97060be, 0xb305f41, 0xb705f3e, 0xb709fbf, 0x970a03f, 0x930a040, 0xb309fc0,
        9, 0x101fc0, 0x10203f, 0xfe040, 0xfdfc0, 0x101fbf, 0xfdfbf, 0xfe03f, 0x102041, 0x101fc1, 0x8105fc0, 0x8106040, 0x810603f, 0x8105fbf, 0xfdfc1, 0xfe041, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x10fe0bf, 0x3101f40, 0x30fdf40, 0x3101f3f, 0x30fdf3f,
        0x8105fc1, 0x8106041, 0x70203e, 0x701fbe, 0x6fdfbe, 0x6fe03e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x11020c1, 0x91060c0, 0x91060bf, 0x12fe0c1, 0x3101f41, 0xb105f40, 0xb105f3f, 0x30fdf41, 0x180f9fc1, 0x182fa041, 0x870603e,
        0x8705fbe, 0x93060c1, 0x17020be, 0x16fe0be, 0x190fa0bf, 0x190fa0c0, 0xb305f41, 0x1b0f9f40, 0x1b0f9f3f, 0x36fdf3e, 0xb701f3e, 0x1b6f9fbe, 0x196fa03e, 0x97060be, 0x192fa0c1, 0x1b2f9f41, 0x1b2fdfc2, 0xb301fc2, 0x11302042,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0x101fbf, 0x10203f, 0xfe03f, 0xfdfbf, 0x101fc1, 0x102041, 0xfe041, 0xfdfc1, 0x8105fc0, 0x8106040, 0x810603f, 0x8105fbf, 0x11020c0, 0x10fe0c0, 0x11020bf, 0x10fe0bf, 0x8106041, 0x8105fc1, 0x3101f40, 0x30fdf40,
        0x3101f3f, 0x30fdf3f, 0x180f9fc0, 0x180fa040, 0x11020c1, 0x10fe0c1, 0x180fa03f, 0x180f9fbf, 0x91060c0, 0x91060bf, 0x3101f41, 0x30fdf41, 0x701fbe, 0x70203e, 0x6fe03e, 0x6fdfbe, 0xb105f40, 0xb105f3f, 0x180f9fc1, 0x180fa041, 0x93060c1,
        0xb305f41, 0x190fa0c0, 0x190fa0bf, 0x870603e, 0x8705fbe, 0x97020be, 0x16fe0be, 0x1b0f9f40, 0x1b0f9f3f, 0x36fdf3e, 0xb701f3e, 0x192fa0c1, 0x192fe042, 0x9302042, 0xb301fc2, 0x1b2fdfc2, 0x1b2f9f41, 0x1b6f9fbe, 0x196fa03e,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0x101fbf, 0x10203f, 0xfe03f, 0xfdfbf, 0x101fc1, 0x102041, 0xfe041, 0xfdfc1, 0x8105fc0, 0x8106040, 0x810603f, 0x8105fbf, 0x11020c0, 0x10fe0c0, 0x8106041, 0x8105fc1, 0x11020bf, 0x10fe0bf, 0x3101f40, 0x30fdf40,
        0x11020c1, 0x10fe0c1, 0x180fa040, 0x3101f3f, 0x30fdf3f, 0x180f9fc0, 0x3101f41, 0x30fdf41, 0x91060c0, 0x180fa03f, 0x180f9fbf, 0x180f9fc1, 0x180fa041, 0x91060bf, 0xb105f40, 0x91060c1, 0xb105f3f, 0x3701fbe, 0x70203e, 0x186fe03e, 0x1b6fdfbe,
        0xb105f41, 0x3301fc2, 0x190fa0c0, 0x190fa0bf, 0x302042, 0x182fe042, 0x1b2fdfc2, 0x1b0f9f40, 0x1b6f9f3f, 0x190fa0c1, 0x870603e, 0xb705fbe, 0x97020be, 0x196fe0be, 0x1b2f9f41, 0xb305fc2, 0x8306042, 0x93020c2, 0x192fe0c2,
        9, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0xfdfbf, 0xfdfc0, 0x1020c0, 0x1020bf, 0x810603f, 0x8106040, 0x8105fc0, 0x8105fbf, 0xfe0bf, 0xfe0c0, 0x302041, 0x301fc1, 0x2fe041, 0x2fdfc1, 0x70203e, 0x6fe03e, 0x701fbe, 0x6fdfbe, 0x81060bf,
        0x81060c0, 0x3101f40, 0x3101f3f, 0x30fdf3f, 0x30fdf40, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x3020c1, 0x8306041, 0x8305fc1, 0x12fe0c1, 0x7020be, 0x870603e, 0x8705fbe, 0x6fe0be, 0x180fa0bf, 0x190fa0c0, 0xb105f40, 0xb105f3f,
        0x93060c1, 0x3301f41, 0x32fdf41, 0x182f9fc1, 0x182fa041, 0x97060be, 0x186fa03e, 0x186f9fbe, 0x36fdf3e, 0xb701f3e, 0x1b6f9f3f, 0x1b2f9f40, 0xb305f41, 0x192fa0c1, 0x196fa0be, 0x196fe13f, 0x970213f, 0x11302140,
        7, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x302041, 0x1020c0, 0x8106040, 0x810603f, 0x1020bf, 0xfe0c0, 0x2fe041, 0x301fc1, 0x8105fc0, 0x8105fbf, 0xfe0bf, 0x2fdfc1, 0x3020c1, 0x8306041, 0x81060c0, 0x81060bf,
        0x2fe0c1, 0x8305fc1, 0x3101f40, 0x3101f3f, 0x701fbe, 0x70203e, 0x6fe03e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x30fdf40, 0x30fdf3f, 0x6fdfbe, 0x180f9fbf, 0x180fa0c0, 0x182fa041, 0x93060c1, 0x870603e, 0x7020be, 0x6fe0be, 0x180fa0bf, 0x182f9fc1,
        0x32fdf41, 0x3301f41, 0xb105f40, 0xb105f3f, 0x8705fbe, 0x97060be, 0x192fa0c1, 0xb305f41, 0xb701f3e, 0x36fdf3e, 0x1b0f9f3f, 0x1b2f9f40, 0x1b6f9fbe, 0x196fa03e, 0x196fe13f, 0x9302140, 0x970213f, 0x192fe140,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0x10203f, 0x101fbf, 0xfe03f, 0xfdfbf, 0x102041, 0x101fc1, 0xfe041, 0xfdfc1, 0x11020c0, 0x8106040, 0x8105fc0, 0x10fe0c0, 0x11020bf, 0x810603f, 0x8105fbf, 0x10fe0bf, 0x11020c1, 0x8106041, 0x8105fc1, 0x10fe0c1,
        0x91060c0, 0x91060bf, 0x3101f40, 0x30fdf40, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x30fdf3f, 0x3101f3f, 0x701fbe, 0x70203e, 0x6fe03e, 0x6fdfbe, 0x93060c1, 0x3101f41, 0x30fdf41, 0x180f9fc1, 0x180fa041, 0x190fa0c0, 0x190fa0bf,
        0xb105f40, 0xb105f3f, 0x8705fbe, 0x870603e, 0x17020be, 0x16fe0be, 0x192fa0c1, 0xb305f41, 0xb301fc2, 0x9302042, 0x192fe042, 0x1b2fdfc2, 0x1b2f9f40, 0x1b0f9f3f, 0x186f9fbe, 0x196fa03e, 0x97060be, 0xb701f3e, 0x1b6fdf3e,
        11, 0x101fc0, 0xfe040, 0xfdfc0, 0x10203f, 0x101fbf, 0xfe03f, 0xfdfbf, 0x102041, 0x101fc1, 0xfe041, 0xfdfc1, 0x11020c0, 0x8106040, 0x8105fc0, 0x10fe0c0, 0x11020bf, 0x810603f, 0x8105fbf, 0x10fe0bf, 0x11020c1, 0x8106041, 0x8105fc1, 0x10fe0c1,
        0x91060c0, 0x91060bf, 0x3101f40, 0x30fdf40, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x30fdf3f, 0x3101f3f, 0x3101f41, 0x91060c1, 0x180fa041, 0x180f9fc1, 0x30fdf41, 0xb105f40, 0x70203e, 0x3701fbe, 0x186fe03e, 0x1b6fdfbe, 0x190fa0c0,
        0x190fa0bf, 0x190fa0c1, 0xb105f3f, 0xb105f41, 0x3301fc2, 0x302042, 0x182fe042, 0x1b2fdfc2, 0x1b0f9f40, 0x17020be, 0x970603e, 0xb705fbe, 0x196fe0be, 0x1b6f9f3f, 0x1b2f9f41, 0x13020c2, 0x9306042, 0xb305fc2, 0x192fe0c2,
        11, 0x10203f, 0xfe040, 0xfe03f, 0x101fbf, 0x101fc0, 0xfdfc0, 0xfdfbf, 0x1020bf, 0x1020c0, 0xfe0c0, 0xfe0bf, 0x810603f, 0x8106040, 0x8105fc0, 0x8105fbf, 0x302041, 0x2fe041, 0x301fc1, 0x2fdfc1, 0x81060c0, 0x81060bf, 0x70203e, 0x6fe03e,
        0x701fbe, 0x6fdfbe, 0x180fa03f, 0x180fa040, 0x3020c1, 0x2fe0c1, 0x180f9fc0, 0x180f9fbf, 0x8306041, 0x8305fc1, 0x7020be, 0x6fe0be, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x870603e, 0x8705fbe, 0x180fa0bf, 0x180fa0c0, 0x93060c1, 0x97060be,
        0x182fa041, 0x182f9fc1, 0xb105f40, 0xb105f3f, 0xb301f41, 0x32fdf41, 0x186fa03e, 0x186f9fbe, 0x36fdf3e, 0xb701f3e, 0x192fa0c1, 0x192fe140, 0x9302140, 0x970213f, 0x196fe13f, 0x196fa0be, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0x10203f, 0xfe040, 0xfe03f, 0x101fc0, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x1020c0, 0x1020bf, 0xfe0c0, 0xfe0bf, 0x302041, 0x8106040, 0x810603f, 0x2fe041, 0x301fc1, 0x8105fc0, 0x8105fbf, 0x2fdfc1, 0x3020c1, 0x81060c0, 0x81060bf, 0x2fe0c1,
        0x8306041, 0x8305fc1, 0x70203e, 0x6fe03e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x6fdfbe, 0x701fbe, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x93060c1, 0x7020be, 0x6fe0be, 0x180fa0bf, 0x180fa0c0, 0x182fa041, 0x182f9fc1,
        0x870603e, 0x8705fbe, 0xb105f3f, 0xb105f40, 0x3301f41, 0x32fdf41, 0x192fa0c1, 0x97060be, 0x970213f, 0x9302140, 0x192fe140, 0x196fe13f, 0x196fa03e, 0x186f9fbe, 0x1b0f9f3f, 0x1b2f9f40, 0xb305f41, 0xb701f3e, 0x1b6fdf3e,
        15, 0xfe040, 0x10203f, 0x101fc0, 0xfdfc0, 0xfe03f, 0x101fbf, 0xfdfbf, 0x102041, 0x1020c0, 0xfe0c0, 0xfe041, 0x101fc1, 0xfdfc1, 0x1020bf, 0xfe0bf, 0x8106040, 0x810603f, 0x8105fc0, 0x8105fbf, 0x1020c1, 0xfe0c1, 0x8106041, 0x81060c0, 0x81060bf,
        0x8105fc1, 0x180fa040, 0x180f9fc0, 0x180fa03f, 0x180f9fbf, 0x93060c1, 0x70203e, 0x6fe03e, 0x3101f40, 0x1b0fdf40, 0x3101f3f, 0x3701fbe, 0x6fdfbe, 0x1b6fdf3f, 0x180fa041, 0x180fa0c0, 0x180fa0bf, 0x180f9fc1, 0x1b0fdf41, 0x3101f41, 0x7020be,
        0x6fe0be, 0x870603e, 0x8705fbe, 0xb105f40, 0xb705f3f, 0x192fa0c1, 0x192fe140, 0x9302140, 0x970213f, 0x97060be, 0x9302042, 0x192fe042, 0xb301fc2, 0xb305f41, 0x1b2fdfc2, 0x196fe13f, 0x196fa03e, 0x1b6f9fbe,
        14, 0xfe040, 0x101fc0, 0xfdfc0, 0x10203f, 0xfe03f, 0x101fbf, 0xfdfbf, 0x102041, 0xfe041, 0x101fc1, 0xfdfc1, 0x1020c0, 0xfe0c0, 0x1020bf, 0x8106040, 0xfe0bf, 0x8105fc0, 0x1020c1, 0xfe0c1, 0x810603f, 0x8105fbf, 0x8106041, 0x8105fc1, 0x81060c0,
        0x81060bf, 0x91060c1, 0x180fa040, 0x180f9fc0, 0x180fa03f, 0x180f9fbf, 0x180fa041, 0x180f9fc1, 0x1b0fdf40, 0x3101f40, 0x3101f3f, 0x1b0fdf3f, 0x180fa0c0, 0x190fa0bf, 0x186fe03e, 0x70203e, 0x3701fbe, 0x3101f41, 0x1b0fdf41, 0x1b6fdfbe,
        0x190fa0c1, 0x182fe042, 0x302042, 0xb105f40, 0xb105f3f, 0x3301fc2, 0x1b2fdfc2, 0x7020be, 0x196fe0be, 0x970603e, 0xb705fbe, 0xb105f41, 0x9302140, 0x192fe140, 0x13020c2, 0x192fe0c2, 0x9306042, 0xb305fc2, 0x1170213f,
        11, 0x10203f, 0xfe040, 0xfe03f, 0x101fbf, 0x101fc0, 0xfdfc0, 0xfdfbf, 0x1020bf, 0x1020c0, 0xfe0c0, 0xfe0bf, 0x810603f, 0x8106040, 0x8105fc0, 0x8105fbf, 0x302041, 0x2fe041, 0x81060c0, 0x81060bf, 0x301fc1, 0x2fdfc1, 0x70203e, 0x6fe03e,
        0x3020c1, 0x2fe0c1, 0x180fa040, 0x701fbe, 0x6fdfbe, 0x180fa03f, 0x7020be, 0x6fe0be, 0x8306041, 0x180f9fc0, 0x180f9fbf, 0x180fa0bf, 0x180fa0c0, 0x8305fc1, 0x870603e, 0x83060c1, 0x8705fbe, 0x3701f3f, 0x3101f40, 0x1b0fdf40, 0x1b6fdf3f,
        0x87060be, 0x170213f, 0x182fa041, 0x182f9fc1, 0x1102140, 0x190fe140, 0x196fe13f, 0x186fa03e, 0x1b6f9fbe, 0x182fa0c1, 0xb105f40, 0xb705f3f, 0xb301f41, 0x1b2fdf41, 0x196fa0be, 0x970613f, 0x9106140, 0x9302141, 0x192fe141,
        11, 0x10203f, 0xfe040, 0xfe03f, 0x101fc0, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x1020c0, 0x1020bf, 0xfe0c0, 0xfe0bf, 0x302041, 0x8106040, 0x810603f, 0x2fe041, 0x301fc1, 0x8105fc0, 0x8105fbf, 0x2fdfc1, 0x3020c1, 0x81060c0, 0x81060bf, 0x2fe0c1,
        0x8306041, 0x8305fc1, 0x70203e, 0x6fe03e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x6fdfbe, 0x701fbe, 0x7020be, 0x83060c1, 0x180fa0c0, 0x180fa0bf, 0x6fe0be, 0x870603e, 0x3101f40, 0x3701f3f, 0x1b0fdf40, 0x1b6fdf3f, 0x182fa041,
        0x182f9fc1, 0x182fa0c1, 0x8705fbe, 0x87060be, 0x170213f, 0x1102140, 0x190fe140, 0x196fe13f, 0x186fa03e, 0x3301f41, 0xb305f40, 0xb705f3f, 0x1b2fdf41, 0x1b6f9fbe, 0x196fa0be, 0x1302141, 0x9306140, 0x970613f, 0x192fe141,
        14, 0xfe040, 0x10203f, 0xfe03f, 0x101fc0, 0xfdfc0, 0x101fbf, 0xfdfbf, 0x1020c0, 0xfe0c0, 0x1020bf, 0xfe0bf, 0x102041, 0xfe041, 0x101fc1, 0x8106040, 0xfdfc1, 0x810603f, 0x1020c1, 0xfe0c1, 0x8105fc0, 0x8105fbf, 0x81060c0, 0x81060bf, 0x8106041,
        0x8105fc1, 0x83060c1, 0x180fa040, 0x180fa03f, 0x180f9fc0, 0x180f9fbf, 0x180fa0c0, 0x180fa0bf, 0x186fe03e, 0x70203e, 0x701fbe, 0x186fdfbe, 0x180fa041, 0x182f9fc1, 0x1b0fdf40, 0x3101f40, 0x3701f3f, 0x7020be, 0x186fe0be, 0x1b6fdf3f, 0x182fa0c1,
        0x190fe140, 0x1102140, 0x870603e, 0x8705fbe, 0x170213f, 0x196fe13f, 0x3101f41, 0x1b2fdf41, 0xb305f40, 0xb705f3f, 0x87060be, 0x9302042, 0x192fe042, 0x1302141, 0x192fe141, 0x9306140, 0x970613f, 0x13301fc2,
        17, 0xfe040, 0x10203f, 0x101fc0, 0xfdfc0, 0xfe03f, 0x1020c0, 0x102041, 0xfe041, 0xfe0c0, 0x101fbf, 0xfdfbf, 0x1020bf, 0xfe0bf, 0x101fc1, 0xfdfc1, 0x1020c1, 0xfe0c1, 0x8106040, 0x810603f, 0x8105fc0, 0x8106041, 0x81060c0, 0x8105fbf, 0x81060bf,
        0x8105fc1, 0x81060c1, 0x180fa040, 0x180f9fc0, 0x180fa03f, 0x180fa0c0, 0x180fa041, 0x180f9fbf, 0x180fa0bf, 0x180f9fc1, 0x180fa0c1, 0x70203e, 0x186fe03e, 0x3101f40, 0x1b0fdf40, 0x3101f3f, 0x3701fbe, 0x186fdfbe, 0x1b6fdf3f, 0x3101f41,
        0x1b0fdf41, 0x8302042, 0x182fe042, 0x9102140, 0x7020be, 0x186fe0be, 0x190fe140, 0x970213f, 0x196fe13f, 0x9102141, 0xb301fc2, 0x1b2fdfc2, 0x93020c2, 0x182fe0c2, 0x192fe141, 0x970603e, 0xb305f40, 0xb105f3f, 0xb705fbe,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfdfbf, 0xfe03f, 0xfe040, 0xfdfc0, 0x105fc0, 0x106040, 0x10603f, 0x105fbf, 0x11020bf, 0x11020c0, 0x302041, 0x301fc1, 0x2fdfc1, 0x2fe041, 0x10fe0c0, 0x10fe0bf, 0x70203e, 0x701fbe, 0x3101f3f, 0x3101f40,
        0x30fdf40, 0x30fdf3f, 0x6fdfbe, 0x6fe03e, 0x11060bf, 0x11060c0, 0x306041, 0x305fc1, 0x3105f40, 0x3105f3f, 0x705fbe, 0x70603e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x13020c1, 0x12fe0c1, 0x17020be, 0x16fe0be, 0x3301f41, 0x32fdf41,
        0x93060c1, 0x3701f3e, 0x36fdf3e, 0x97060be, 0xb305f41, 0x182f9fc1, 0x182fa041, 0x192fa0c0, 0x190fa0bf, 0x196fa03e, 0x186f9fbe, 0xb705f3e, 0xb709fbf, 0xb309fc0, 0x930a040, 0x970a03f, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0x101fc0, 0x10203f, 0x101fbf, 0xfdfc0, 0xfe040, 0xfe03f, 0xfdfbf, 0x105fc0, 0x106040, 0x10603f, 0x105fbf, 0x301fc1, 0x302041, 0x2fe041, 0x2fdfc1, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x10fe0bf, 0x306041, 0x305fc1, 0x3101f40, 0x3101f3f,
        0x30fdf40, 0x30fdf3f, 0x701fbe, 0x70203e, 0x11060c0, 0x11060bf, 0x6fe03e, 0x6fdfbe, 0x13020c1, 0x12fe0c1, 0x3105f40, 0x3105f3f, 0x180f9fc0, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x3301f41, 0x32fdf41, 0x705fbe, 0x70603e, 0x93060c1, 0xb305f41,
        0x17020be, 0x16fe0be, 0x182fa041, 0x182f9fc1, 0x192fa0c0, 0x190fa0bf, 0x3701f3e, 0x36fdf3e, 0x1b0f9f3f, 0x1b2f9f40, 0x97060be, 0x970a03f, 0x930a040, 0xb309fc0, 0xb709fbf, 0xb705f3e, 0x1b6f9fbe, 0x196fa03e,
        15, 0x101fc0, 0x101fbf, 0x10203f, 0xfe040, 0xfdfc0, 0xfdfbf, 0xfe03f, 0x102041, 0x101fc1, 0x105fc0, 0x106040, 0x10603f, 0x105fbf, 0xfdfc1, 0xfe041, 0x11020c0, 0x106041, 0x105fc1, 0x11020bf, 0x10fe0c0, 0x10fe0bf, 0x3101f40, 0x3101f3f,
        0x30fdf40, 0x30fdf3f, 0x11020c1, 0x11060c0, 0x11060bf, 0x10fe0c1, 0x3101f41, 0x3105f40, 0x3105f3f, 0x701fbe, 0x70203e, 0x180fa040, 0x180f9fc0, 0x30fdf41, 0x180f9fbf, 0x180fa03f, 0x186fe03e, 0x186fdfbe, 0x93060c1, 0xb305f41, 0x705fbe,
        0x70603e, 0x180fa041, 0x180f9fc1, 0x192fa0c0, 0x190fa0bf, 0x97020be, 0x196fe0be, 0xb701f3e, 0x36fdf3e, 0x1b2f9f40, 0x1b6f9f3f, 0xb301fc2, 0x9302042, 0x192fe042, 0x1b2fdfc2, 0xb309fc0, 0x930a040, 0x970a03f, 0xb709fbf,
        15, 0x101fc0, 0xfdfc0, 0xfe040, 0x10203f, 0x101fbf, 0xfdfbf, 0xfe03f, 0x102041, 0x101fc1, 0xfdfc1, 0xfe041, 0x106040, 0x105fc0, 0x105fbf, 0x10603f, 0x106041, 0x105fc1, 0x11020c0, 0x10fe0c0, 0x11020bf, 0x10fe0bf, 0x3101f40, 0x30fdf40,
        0x11020c1, 0x10fe0c1, 0x11060c0, 0x3101f3f, 0x30fdf3f, 0x3101f41, 0x30fdf41, 0x3105f40, 0x11060bf, 0x91060c1, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x3105f3f, 0xb105f41, 0x180fa03f, 0x180fa041, 0x180f9fc1, 0x3701fbe, 0x70203e, 0x186fe03e,
        0x1b6fdfbe, 0x3705fbe, 0x70603e, 0x1302042, 0x3301fc2, 0x1b2fdfc2, 0x192fe042, 0x190fa0c0, 0x196fa0bf, 0x192fa0c1, 0x1b2f9f40, 0x1b6f9f3f, 0xb309fc0, 0x930a040, 0x9306042, 0xb305fc2, 0xb709fbf, 0x970a03f, 0x117020be,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfe03f, 0xfe040, 0xfdfc0, 0xfdfbf, 0x10603f, 0x106040, 0x105fc0, 0x105fbf, 0x11020bf, 0x11020c0, 0x10fe0c0, 0x10fe0bf, 0x302041, 0x301fc1, 0x2fe041, 0x2fdfc1, 0x11060c0, 0x11060bf, 0x70203e, 0x701fbe,
        0x6fe03e, 0x6fdfbe, 0x3101f3f, 0x3101f40, 0x306041, 0x305fc1, 0x30fdf40, 0x30fdf3f, 0x13020c1, 0x12fe0c1, 0x70603e, 0x705fbe, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x17020be, 0x16fe0be, 0x3105f3f, 0x3105f40, 0x93060c1, 0x97060be,
        0x3301f41, 0x32fdf41, 0x190fa0c0, 0x190fa0bf, 0x192fa041, 0x182f9fc1, 0x3701f3e, 0x36fdf3e, 0x186f9fbe, 0x196fa03e, 0xb305f41, 0xb309fc0, 0x930a040, 0x970a03f, 0xb709fbf, 0xb705f3e, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfe040, 0xfe03f, 0xfdfc0, 0xfdfbf, 0x106040, 0x10603f, 0x105fc0, 0x105fbf, 0x302041, 0x11020c0, 0x11020bf, 0x301fc1, 0x2fe041, 0x10fe0c0, 0x10fe0bf, 0x2fdfc1, 0x306041, 0x11060c0, 0x11060bf, 0x305fc1,
        0x13020c1, 0x12fe0c1, 0x70203e, 0x701fbe, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x6fdfbe, 0x6fe03e, 0x180fa03f, 0x180fa040, 0x180f9fc0, 0x180f9fbf, 0x93060c1, 0x70603e, 0x705fbe, 0x3105f3f, 0x3105f40, 0x3301f41, 0x32fdf41, 0x17020be,
        0x16fe0be, 0x190fa0bf, 0x190fa0c0, 0x182fa041, 0x182f9fc1, 0xb305f41, 0x97060be, 0x970a03f, 0x930a040, 0xb309fc0, 0xb709fbf, 0xb701f3e, 0x36fdf3e, 0x1b0f9f3f, 0x1b2f9f40, 0x192fa0c1, 0x196fa03e, 0x1b6f9fbe,
        15, 0x101fc0, 0x10203f, 0xfe040, 0xfdfc0, 0x101fbf, 0xfe03f, 0xfdfbf, 0x102041, 0x106040, 0x105fc0, 0x101fc1, 0xfe041, 0xfdfc1, 0x10603f, 0x105fbf, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x10fe0bf, 0x106041, 0x105fc1, 0x11020c1, 0x11060c0,
        0x11060bf, 0x10fe0c1, 0x3101f40, 0x30fdf40, 0x3101f3f, 0x30fdf3f, 0x93060c1, 0x70203e, 0x701fbe, 0x180fa040, 0x1b0f9fc0, 0x180fa03f, 0x186fe03e, 0x6fdfbe, 0x1b6f9fbf, 0x3101f41, 0x3105f40, 0x3105f3f, 0x30fdf41, 0x1b0f9fc1, 0x180fa041,
        0x70603e, 0x705fbe, 0x17020be, 0x16fe0be, 0x190fa0c0, 0x196fa0bf, 0xb305f41, 0xb309fc0, 0x930a040, 0x970a03f, 0x97060be, 0x9302042, 0xb301fc2, 0x192fe042, 0x192fa0c1, 0x1b2fdfc2, 0xb709fbf, 0xb701f3e, 0x1b6fdf3e,
        14, 0x101fc0, 0xfe040, 0xfdfc0, 0x10203f, 0x101fbf, 0xfe03f, 0xfdfbf, 0x102041, 0x101fc1, 0xfe041, 0xfdfc1, 0x106040, 0x105fc0, 0x10603f, 0x11020c0, 0x105fbf, 0x10fe0c0, 0x106041, 0x105fc1, 0x11020bf, 0x10fe0bf, 0x11020c1, 0x10fe0c1,
        0x11060c0, 0x11060bf, 0x91060c1, 0x3101f40, 0x30fdf40, 0x3101f3f, 0x30fdf3f, 0x3101f41, 0x30fdf41, 0x1b0f9fc0, 0x180fa040, 0x180fa03f, 0x1b0f9fbf, 0x3105f40, 0xb105f3f, 0x3701fbe, 0x70203e, 0x186fe03e, 0x180fa041, 0x1b0f9fc1, 0x1b6fdfbe,
        0xb105f41, 0x3301fc2, 0x302042, 0x190fa0c0, 0x190fa0bf, 0x182fe042, 0x1b2fdfc2, 0x70603e, 0xb705fbe, 0x97020be, 0x196fe0be, 0x190fa0c1, 0x930a040, 0xb309fc0, 0x8306042, 0xb305fc2, 0x93020c2, 0x192fe0c2, 0xa70a03f,
        15, 0x10203f, 0x101fbf, 0x101fc0, 0xfe040, 0xfe03f, 0xfdfbf, 0xfdfc0, 0x1020c0, 0x1020bf, 0x10603f, 0x106040, 0x105fc0, 0x105fbf, 0xfe0bf, 0xfe0c0, 0x302041, 0x1060c0, 0x1060bf, 0x301fc1, 0x2fe041, 0x2fdfc1, 0x70203e, 0x701fbe, 0x6fe03e,
        0x6fdfbe, 0x3020c1, 0x306041, 0x305fc1, 0x2fe0c1, 0x7020be, 0x70603e, 0x705fbe, 0x3101f3f, 0x3101f40, 0x180fa040, 0x180fa03f, 0x6fe0be, 0x180f9fbf, 0x180f9fc0, 0x1b0fdf40, 0x1b0fdf3f, 0x93060c1, 0x97060be, 0x3105f3f, 0x3105f40, 0x180fa0c0,
        0x180fa0bf, 0x192fa041, 0x182f9fc1, 0xb301f41, 0x1b2fdf41, 0xb701f3e, 0x36fdf3e, 0x196fa03e, 0x1b6f9fbe, 0x970213f, 0x9302140, 0x192fe140, 0x196fe13f, 0x970a03f, 0x930a040, 0xb309fc0, 0xb709fbf,
        15, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x1020c0, 0x106040, 0x10603f, 0x1020bf, 0xfe0c0, 0xfe0bf, 0x105fc0, 0x105fbf, 0x302041, 0x301fc1, 0x2fe041, 0x2fdfc1, 0x1060c0, 0x1060bf, 0x3020c1, 0x306041, 0x305fc1,
        0x2fe0c1, 0x70203e, 0x6fe03e, 0x701fbe, 0x6fdfbe, 0x93060c1, 0x3101f40, 0x3101f3f, 0x180fa040, 0x186fa03f, 0x180f9fc0, 0x1b0fdf40, 0x30fdf3f, 0x1b6f9fbf, 0x7020be, 0x70603e, 0x705fbe, 0x6fe0be, 0x186fa0bf, 0x180fa0c0, 0x3105f40, 0x3105f3f,
        0x3301f41, 0x32fdf41, 0x182fa041, 0x1b2f9fc1, 0x97060be, 0x970a03f, 0x930a040, 0xb309fc0, 0xb305f41, 0x9302140, 0x970213f, 0x192fe140, 0x192fa0c1, 0x196fe13f, 0xb709fbf, 0xb701f3e, 0x1b6fdf3e,
        16, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x102041, 0x1020c0, 0x106040, 0x10603f, 0x1020bf, 0xfe0c0, 0xfe041, 0x101fc1, 0x105fc0, 0x105fbf, 0xfe0bf, 0xfdfc1, 0x1020c1, 0x106041, 0x1060c0, 0x1060bf, 0xfe0c1,
        0x105fc1, 0x93060c1, 0x70203e, 0x3101f40, 0x180fa040, 0x180fa03f, 0x186fe03e, 0x701fbe, 0x3701f3f, 0x30fdf40, 0x1b0f9fc0, 0x180f9fbf, 0x186fdfbe, 0x1b6fdf3f, 0x3101f41, 0x3105f40, 0xb105f3f, 0x70603e, 0x7020be, 0x6fe0be, 0x180fa0c0,
        0x180fa041, 0x182f9fc1, 0x1b2fdf41, 0xb705fbe, 0x186fa0bf, 0x192fa0c1, 0x97060be, 0xb305f41, 0x9302042, 0x192fe042, 0x13301fc2, 0x930a040, 0x970a03f, 0xb509fc0, 0x9302140, 0x970213f, 0x192fe140, 0x196fe13f,
        15, 0x101fc0, 0xfe040, 0xfdfc0, 0x10203f, 0x101fbf, 0xfe03f, 0x102041, 0x101fc1, 0xfdfbf, 0xfe041, 0x1020c0, 0x106040, 0xfdfc1, 0x105fc0, 0xfe0c0, 0x1020bf, 0x10603f, 0x105fbf, 0xfe0bf, 0x1020c1, 0x106041, 0x105fc1, 0xfe0c1, 0x1060c0,
        0x11060bf, 0x91060c1, 0x3101f40, 0x180fa040, 0x180f9fc0, 0x1b0fdf40, 0x3101f3f, 0x30fdf3f, 0x180fa03f, 0x1b0f9fbf, 0x180fa041, 0x180f9fc1, 0x3101f41, 0x1b0fdf41, 0x70203e, 0x3701fbe, 0x186fe03e, 0x1b6fdfbe, 0x3105f40, 0xb105f3f, 0x180fa0c0,
        0x190fa0bf, 0x192fa0c1, 0x302042, 0x3301fc2, 0xb305f41, 0x182fe042, 0x1b2fdfc2, 0x17020be, 0x170603e, 0xb705fbe, 0x196fe0be, 0x9502140, 0x194fe140, 0x193020c2, 0xa306042, 0x930a040, 0xb309fc0, 0xa70a03f,
        15, 0x10203f, 0xfe03f, 0xfe040, 0x101fc0, 0x101fbf, 0xfdfbf, 0xfdfc0, 0x1020c0, 0x1020bf, 0xfe0bf, 0xfe0c0, 0x106040, 0x10603f, 0x105fbf, 0x105fc0, 0x1060c0, 0x1060bf, 0x302041, 0x2fe041, 0x301fc1, 0x2fdfc1, 0x70203e, 0x6fe03e, 0x3020c1,
        0x2fe0c1, 0x306041, 0x701fbe, 0x6fdfbe, 0x7020be, 0x6fe0be, 0x70603e, 0x305fc1, 0x83060c1, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x705fbe, 0x87060be, 0x180f9fc0, 0x180fa0c0, 0x180fa0bf, 0x3701f3f, 0x3101f40, 0x1b0fdf40, 0x1b6fdf3f, 0x3705f3f,
        0x3105f40, 0x1302140, 0x170213f, 0x196fe13f, 0x192fe140, 0x182fa041, 0x1b2f9fc1, 0x192fa0c1, 0x196fa03e, 0x1b6f9fbe, 0x970a03f, 0x930a040, 0x9306140, 0x970613f, 0xb709fbf, 0xb309fc0, 0x13301f41,
        14, 0x10203f, 0xfe040, 0xfe03f, 0x101fc0, 0x101fbf, 0xfdfc0, 0xfdfbf, 0x1020c0, 0x1020bf, 0xfe0c0, 0xfe0bf, 0x106040, 0x10603f, 0x105fc0, 0x302041, 0x105fbf, 0x2fe041, 0x1060c0, 0x1060bf, 0x301fc1, 0x2fdfc1, 0x3020c1, 0x2fe0c1, 0x306041,
        0x305fc1, 0x83060c1, 0x70203e, 0x6fe03e, 0x701fbe, 0x6fdfbe, 0x7020be, 0x6fe0be, 0x186fa03f, 0x180fa040, 0x180f9fc0, 0x186f9fbf, 0x70603e, 0x8705fbe, 0x3701f3f, 0x3101f40, 0x1b0fdf40, 0x180fa0c0, 0x186fa0bf, 0x1b6fdf3f, 0x87060be, 0x170213f,
        0x1102140, 0x182fa041, 0x182f9fc1, 0x190fe140, 0x196fe13f, 0x3105f40, 0xb705f3f, 0xb301f41, 0x1b2fdf41, 0x182fa0c1, 0x930a040, 0x970a03f, 0x9106140, 0x970613f, 0x9302141, 0x192fe141, 0xb509fc0,
        15, 0x10203f, 0xfe040, 0xfe03f, 0x101fc0, 0x101fbf, 0xfdfc0, 0x1020c0, 0x1020bf, 0xfdfbf, 0xfe0c0, 0x102041, 0x106040, 0xfe0bf, 0x10603f, 0xfe041, 0x101fc1, 0x105fc0, 0x105fbf, 0xfdfc1, 0x1020c1, 0x1060c0, 0x1060bf, 0xfe0c1, 0x106041,
        0x305fc1, 0x83060c1, 0x70203e, 0x180fa040, 0x180fa03f, 0x186fe03e, 0x701fbe, 0x6fdfbe, 0x180f9fc0, 0x186f9fbf, 0x180fa0c0, 0x180fa0bf, 0x7020be, 0x186fe0be, 0x3101f40, 0x3701f3f, 0x1b0fdf40, 0x1b6fdf3f, 0x70603e, 0x8705fbe, 0x180fa041,
        0x182f9fc1, 0x192fa0c1, 0x1102140, 0x170213f, 0x97060be, 0x190fe140, 0x196fe13f, 0x3301f41, 0x3305f40, 0xb705f3f, 0x1b2fdf41, 0xa302042, 0x1a2fe042, 0x19302141, 0x9506140, 0x930a040, 0x970a03f, 0xb509fc0,
        17, 0xfe040, 0x10203f, 0x101fc0, 0xfdfc0, 0xfe03f, 0x1020c0, 0x102041, 0x101fbf, 0xfe041, 0xfe0c0, 0x106040, 0xfdfbf, 0x1020bf, 0x101fc1, 0xfdfc1, 0xfe0bf, 0x1020c1, 0x10603f, 0x105fc0, 0xfe0c1, 0x1060c0, 0x106041, 0x8105fbf, 0x81060bf,
        0x8105fc1, 0x81060c1, 0x180fa040, 0x180f9fc0, 0x180fa03f, 0x180fa0c0, 0x180fa041, 0x180f9fbf, 0x70203e, 0x186fe03e, 0x3101f40, 0x1b0fdf40, 0x180f9fc1, 0x180fa0bf, 0x701fbe, 0x3701f3f, 0x1b0fdf3f, 0x1b6fdfbe, 0x7020be, 0x186fe0be, 0x192fa0c1,
        0x9102140, 0x190fe140, 0x8302042, 0x3101f41, 0x1b0fdf41, 0x182fe042, 0xb301fc2, 0xb305f40, 0x870603e, 0x970213f, 0x196fe13f, 0x11102141, 0x113020c2, 0x1b2fdfc2, 0xb105f3f, 0xb705fbe, 0x97060be, 0xa50a040,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfdfbf, 0xfe03f, 0xfe040, 0xfdfc0, 0x105fc0, 0x106040, 0x10603f, 0x105fbf, 0x11020bf, 0x11020c0, 0x302041, 0x301fc1, 0x2fdfc1, 0x2fe041, 0x10fe0c0, 0x10fe0bf, 0x70203e, 0x701fbe, 0x3101f3f, 0x3101f40,
        0x305fc1, 0x306041, 0x11060c0, 0x11060bf, 0x6fe03e, 0x6fdfbe, 0x30fdf3f, 0x30fdf40, 0x3105f40, 0x3105f3f, 0x705fbe, 0x70603e, 0x13020c1, 0x12fe0c1, 0x180fa040, 0x180fa03f, 0x180f9fbf, 0x180f9fc0, 0x3301f41, 0x17020be, 0x16fe0be, 0x93060c1,
        0x32fdf41, 0xb305f41, 0x3701f3e, 0x36fdf3e, 0x97060be, 0x970a03f, 0x930a040, 0xb309fc0, 0xb709fbf, 0xb705f3e, 0x182f9fc1, 0x182fa041, 0x192fa0c0, 0x190fa0bf, 0x196fa03e, 0x186f9fbe, 0x1b6f9f3f, 0x1b2f9f40,
        11, 0x101fc0, 0x10203f, 0x101fbf, 0xfdfc0, 0xfe040, 0xfe03f, 0xfdfbf, 0x105fc0, 0x106040, 0x10603f, 0x105fbf, 0x301fc1, 0x302041, 0x2fe041, 0x2fdfc1, 0x11020c0, 0x11020bf, 0x306041, 0x305fc1, 0x10fe0c0, 0x10fe0bf, 0x3101f40, 0x3101f3f,
        0x11060c0, 0x11060bf, 0x70203e, 0x30fdf40, 0x30fdf3f, 0x701fbe, 0x3105f40, 0x3105f3f, 0x13020c1, 0x6fe03e, 0x6fdfbe, 0x705fbe, 0x70603e, 0x12fe0c1, 0x3301f41, 0x13060c1, 0x32fdf41, 0x1b0f9fc0, 0x180fa040, 0x186fa03f, 0x1b6f9fbf, 0x3305f41,
        0xb109fc0, 0x17020be, 0x16fe0be, 0x810a040, 0x870a03f, 0xb709fbf, 0x3701f3e, 0x1b6fdf3e, 0x17060be, 0x182fa041, 0x1b2f9fc1, 0x192fa0c0, 0x196fa0bf, 0xb705f3e, 0xb309fc1, 0x830a041, 0x930a0c0, 0x970a0bf,
        15, 0x101fc0, 0x101fbf, 0x10203f, 0xfe040, 0xfdfc0, 0xfdfbf, 0xfe03f, 0x106040, 0x105fc0, 0x105fbf, 0x10603f, 0x102041, 0x101fc1, 0xfdfc1, 0xfe041, 0x106041, 0x105fc1, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x10fe0bf, 0x3101f40, 0x3101f3f,
        0x11060c0, 0x11060bf, 0x11020c1, 0x30fdf40, 0x30fdf3f, 0x3105f40, 0x3105f3f, 0x3101f41, 0x10fe0c1, 0x13060c1, 0x70203e, 0x701fbe, 0x6fdfbe, 0x30fdf41, 0x3305f41, 0x6fe03e, 0x70603e, 0x705fbe, 0x1b0f9fc0, 0x180fa040, 0x186fa03f, 0x1b6f9fbf,
        0x1b0f9fc1, 0x180fa041, 0x910a040, 0xb109fc0, 0xb709fbf, 0x970a03f, 0x17020be, 0x196fe0be, 0x97060be, 0xb701f3e, 0x1b6fdf3e, 0xb301fc2, 0x9302042, 0x930a041, 0xb309fc1, 0x1b2fdfc2, 0x192fe042, 0x194fa0c0,
        17, 0x101fc0, 0x101fbf, 0x10203f, 0xfe040, 0xfdfc0, 0x101fc1, 0x102041, 0x106040, 0x105fc0, 0xfdfbf, 0xfe03f, 0x10603f, 0x105fbf, 0xfdfc1, 0xfe041, 0x106041, 0x105fc1, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x11020c1, 0x11060c0, 0x3101f40,
        0x3101f3f, 0x30fdf40, 0x10fe0bf, 0x11060bf, 0x10fe0c1, 0x3101f41, 0x3105f40, 0x30fdf3f, 0x11060c1, 0x3105f3f, 0x30fdf41, 0x3105f41, 0x3701fbe, 0x70203e, 0x180fa040, 0x1b0f9fc0, 0x1b0f9fbf, 0x180fa03f, 0x186fe03e, 0x1b6fdfbe, 0x3705fbe,
        0x70603e, 0x910a040, 0xb109fc0, 0x3301fc2, 0x1302042, 0x180fa041, 0x1b0f9fc1, 0x1b2fdfc2, 0x192fe042, 0x1306042, 0x3305fc2, 0xb709fbf, 0x970a03f, 0x930a041, 0xb309fc1, 0x97020be, 0x192fa0c0, 0x190fa0bf, 0x196fe0be,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfe03f, 0xfe040, 0xfdfc0, 0xfdfbf, 0x10603f, 0x106040, 0x105fc0, 0x105fbf, 0x11020bf, 0x11020c0, 0x10fe0c0, 0x10fe0bf, 0x302041, 0x301fc1, 0x11060c0, 0x11060bf, 0x2fe041, 0x2fdfc1, 0x70203e, 0x701fbe,
        0x306041, 0x305fc1, 0x3101f40, 0x6fe03e, 0x6fdfbe, 0x3101f3f, 0x70603e, 0x705fbe, 0x13020c1, 0x30fdf40, 0x30fdf3f, 0x3105f3f, 0x3105f40, 0x12fe0c1, 0x17020be, 0x13060c1, 0x16fe0be, 0x186fa03f, 0x180fa040, 0x1b0f9fc0, 0x1b6f9fbf, 0x17060be,
        0x870a03f, 0x3301f41, 0x32fdf41, 0x810a040, 0xb109fc0, 0xb709fbf, 0x3701f3e, 0x1b6fdf3e, 0x3305f41, 0x190fa0c0, 0x196fa0bf, 0x192fa041, 0x1b2f9fc1, 0xb705f3e, 0x970a0bf, 0x910a0c0, 0x930a041, 0xb309fc1,
        11, 0x10203f, 0x101fc0, 0x101fbf, 0xfe040, 0xfe03f, 0xfdfc0, 0xfdfbf, 0x106040, 0x10603f, 0x105fc0, 0x105fbf, 0x302041, 0x11020c0, 0x11020bf, 0x301fc1, 0x2fe041, 0x10fe0c0, 0x10fe0bf, 0x2fdfc1, 0x306041, 0x11060c0, 0x11060bf, 0x305fc1,
        0x13020c1, 0x12fe0c1, 0x70203e, 0x701fbe, 0x3101f3f, 0x3101f40, 0x30fdf40, 0x30fdf3f, 0x6fdfbe, 0x6fe03e, 0x70603e, 0x13060c1, 0x3105f40, 0x3105f3f, 0x705fbe, 0x17020be, 0x180fa040, 0x186fa03f, 0x1b0f9fc0, 0x1b6f9fbf, 0x3301f41, 0x32fdf41,
        0x3305f41, 0x16fe0be, 0x17060be, 0x870a03f, 0x810a040, 0xb109fc0, 0xb709fbf, 0x3701f3e, 0x182fa041, 0x192fa0c0, 0x196fa0bf, 0x1b2f9fc1, 0x1b6fdf3e, 0xb705f3e, 0x830a041, 0x930a0c0, 0x970a0bf, 0xb309fc1,
        14, 0x101fc0, 0x10203f, 0x101fbf, 0xfe040, 0xfdfc0, 0xfe03f, 0xfdfbf, 0x106040, 0x105fc0, 0x10603f, 0x105fbf, 0x102041, 0x101fc1, 0xfe041, 0x11020c0, 0xfdfc1, 0x11020bf, 0x106041, 0x105fc1, 0x10fe0c0, 0x10fe0bf, 0x11060c0, 0x11060bf,
        0x11020c1, 0x10fe0c1, 0x13060c1, 0x3101f40, 0x3101f3f, 0x30fdf40, 0x30fdf3f, 0x3105f40, 0x3105f3f, 0x3701fbe, 0x70203e, 0x6fe03e, 0x36fdfbe, 0x3101f41, 0x32fdf41, 0x1b0f9fc0, 0x180fa040, 0x186fa03f, 0x70603e, 0x3705fbe, 0x1b6f9fbf, 0x3305f41,
        0xb109fc0, 0x810a040, 0x17020be, 0x16fe0be, 0x870a03f, 0xb709fbf, 0x180fa041, 0x1b2f9fc1, 0x192fa0c0, 0x196fa0bf, 0x17060be, 0x9302042, 0xb301fc2, 0x830a041, 0xb309fc1, 0x930a0c0, 0x970a0bf, 0x1a2fe042,
        17, 0x101fc0, 0x10203f, 0xfe040, 0xfdfc0, 0x101fbf, 0x106040, 0x102041, 0x101fc1, 0x105fc0, 0xfe03f, 0xfdfbf, 0x10603f, 0x105fbf, 0xfe041, 0xfdfc1, 0x106041, 0x105fc1, 0x11020c0, 0x11020bf, 0x10fe0c0, 0x11020c1, 0x11060c0, 0x10fe0bf,
        0x11060bf, 0x10fe0c1, 0x11060c1, 0x3101f40, 0x30fdf40, 0x3101f3f, 0x3105f40, 0x3101f41, 0x30fdf3f, 0x3105f3f, 0x30fdf41, 0x3105f41, 0x70203e, 0x3701fbe, 0x180fa040, 0x1b0f9fc0, 0x180fa03f, 0x186fe03e, 0x36fdfbe, 0x1b6f9fbf, 0x180fa041,
        0x1b0f9fc1, 0x1302042, 0x3301fc2, 0x910a040, 0x70603e, 0x3705fbe, 0xb109fc0, 0x970a03f, 0xb709fbf, 0x910a041, 0x192fe042, 0x1b2fdfc2, 0x9306042, 0x3305fc2, 0xb309fc1, 0x97020be, 0x192fa0c0, 0x190fa0bf, 0x196fe0be,
        15, 0x10203f, 0x101fbf, 0x101fc0, 0xfe040, 0xfe03f, 0xfdfbf, 0xfdfc0, 0x106040, 0x10603f, 0x105fbf, 0x105fc0, 0x1020c0, 0x1020bf, 0xfe0bf, 0xfe0c0, 0x1060c0, 0x1060bf, 0x302041, 0x301fc1, 0x2fe041, 0x2fdfc1, 0x70203e, 0x701fbe, 0x306041,
        0x305fc1, 0x3020c1, 0x6fe03e, 0x6fdfbe, 0x70603e, 0x705fbe, 0x7020be, 0x2fe0c1, 0x13060c1, 0x3101f40, 0x3101f3f, 0x30fdf3f, 0x6fe0be, 0x17060be, 0x30fdf40, 0x3105f40, 0x3105f3f, 0x186fa03f, 0x180fa040, 0x1b0f9fc0, 0x1b6f9fbf, 0x186fa0bf,
        0x180fa0c0, 0x830a040, 0x870a03f, 0xb709fbf, 0xb309fc0, 0x3301f41, 0x1b2fdf41, 0xb305f41, 0xb701f3e, 0x1b6fdf3e, 0x970213f, 0x9302140, 0x930a0c0, 0x970a0bf, 0x196fe13f, 0x192fe140, 0x1a2fa041,
        14, 0x10203f, 0x101fc0, 0x101fbf, 0xfe040, 0xfe03f, 0xfdfc0, 0xfdfbf, 0x106040, 0x10603f, 0x105fc0, 0x105fbf, 0x1020c0, 0x1020bf, 0xfe0c0, 0x302041, 0xfe0bf, 0x301fc1, 0x1060c0, 0x1060bf, 0x2fe041, 0x2fdfc1, 0x306041, 0x305fc1, 0x3020c1,
        0x2fe0c1, 0x13060c1, 0x70203e, 0x701fbe, 0x6fe03e, 0x6fdfbe, 0x70603e, 0x705fbe, 0x3701f3f, 0x3101f40, 0x30fdf40, 0x36fdf3f, 0x7020be, 0x16fe0be, 0x186fa03f, 0x180fa040, 0x1b0f9fc0, 0x3105f40, 0x3705f3f, 0x1b6f9fbf, 0x17060be, 0x870a03f,
        0x810a040, 0x3301f41, 0x32fdf41, 0xb109fc0, 0xb709fbf, 0x180fa0c0, 0x196fa0bf, 0x192fa041, 0x1b2f9fc1, 0x3305f41, 0x9302140, 0x970213f, 0x910a0c0, 0x970a0bf, 0x930a041, 0xb309fc1, 0x194fe140,
        15, 0x10203f, 0x101fc0, 0x101fbf, 0xfe040, 0xfe03f, 0xfdfc0, 0x106040, 0x10603f, 0xfdfbf, 0x105fc0, 0x102041, 0x1020c0, 0x105fbf, 0x1020bf, 0x101fc1, 0xfe041, 0xfe0c0, 0xfe0bf, 0xfdfc1, 0x106041, 0x1060c0, 0x1060bf, 0x105fc1, 0x1020c1,
        0x2fe0c1, 0x13060c1, 0x70203e, 0x3101f40, 0x3101f3f, 0x3701fbe, 0x6fe03e, 0x6fdfbe, 0x30fdf40, 0x36fdf3f, 0x3105f40, 0x3105f3f, 0x70603e, 0x3705fbe, 0x180fa040, 0x186fa03f, 0x1b0f9fc0, 0x1b6f9fbf, 0x7020be, 0x16fe0be, 0x3101f41, 0x32fdf41,
        0xb305f41, 0x810a040, 0x870a03f, 0x97060be, 0xb109fc0, 0xb709fbf, 0x182fa041, 0x182fa0c0, 0x196fa0bf, 0x1b2f9fc1, 0x11302042, 0x13301fc2, 0xb30a041, 0x950a0c0, 0x9302140, 0x970213f, 0x194fe140,
        17, 0x101fc0, 0x10203f, 0xfe040, 0xfdfc0, 0x101fbf, 0x106040, 0x102041, 0xfe03f, 0x101fc1, 0x105fc0, 0x1020c0, 0xfdfbf, 0x10603f, 0xfe041, 0xfdfc1, 0x105fbf, 0x106041, 0x1020bf, 0xfe0c0, 0x105fc1, 0x1060c0, 0x1020c1, 0x10fe0bf, 0x11060bf,
        0x10fe0c1, 0x11060c1, 0x3101f40, 0x30fdf40, 0x3101f3f, 0x3105f40, 0x3101f41, 0x30fdf3f, 0x70203e, 0x3701fbe, 0x180fa040, 0x1b0f9fc0, 0x30fdf41, 0x3105f3f, 0x6fe03e, 0x186fa03f, 0x1b0f9fbf, 0x1b6fdfbe, 0x70603e, 0x3705fbe, 0xb305f41,
        0x910a040, 0xb109fc0, 0x1302042, 0x180fa041, 0x1b0f9fc1, 0x3301fc2, 0x192fe042, 0x192fa0c0, 0x17020be, 0x970a03f, 0xb709fbf, 0xa10a041, 0xa306042, 0x1b2fdfc2, 0x190fa0bf, 0x196fe0be, 0x97060be, 0x11502140,
        17, 0x10203f, 0x101fbf, 0x101fc0, 0xfe040, 0xfe03f, 0x1020bf, 0x1020c0, 0x106040, 0x10603f, 0xfdfbf, 0xfdfc0, 0x105fc0, 0x105fbf, 0xfe0bf, 0xfe0c0, 0x1060c0, 0x1060bf, 0x302041, 0x301fc1, 0x2fe041, 0x3020c1, 0x306041, 0x70203e, 0x701fbe,
        0x6fe03e, 0x2fdfc1, 0x305fc1, 0x2fe0c1, 0x7020be, 0x70603e, 0x6fdfbe, 0x3060c1, 0x705fbe, 0x6fe0be, 0x7060be, 0x3701f3f, 0x3101f40, 0x180fa040, 0x186fa03f, 0x186f9fbf, 0x180f9fc0, 0x1b0fdf40, 0x1b6fdf3f, 0x3705f3f, 0x3105f40, 0x830a040,
        0x870a03f, 0x170213f, 0x1302140, 0x180fa0c0, 0x186fa0bf, 0x196fe13f, 0x192fe140, 0x1306140, 0x170613f, 0xb709fbf, 0xb309fc0, 0x930a0c0, 0x970a0bf, 0xb301f41, 0x192fa041, 0x182f9fc1, 0x1b2fdf41,
        17, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0x106040, 0x1020c0, 0x1020bf, 0x10603f, 0xfdfc0, 0xfdfbf, 0x105fc0, 0x105fbf, 0xfe0c0, 0xfe0bf, 0x1060c0, 0x1060bf, 0x302041, 0x301fc1, 0x2fe041, 0x3020c1, 0x306041, 0x2fdfc1, 0x305fc1,
        0x2fe0c1, 0x3060c1, 0x70203e, 0x6fe03e, 0x701fbe, 0x70603e, 0x7020be, 0x6fdfbe, 0x705fbe, 0x6fe0be, 0x7060be, 0x3101f40, 0x3701f3f, 0x180fa040, 0x186fa03f, 0x180f9fc0, 0x1b0fdf40, 0x36fdf3f, 0x1b6f9fbf, 0x180fa0c0, 0x186fa0bf, 0x1302140,
        0x170213f, 0x830a040, 0x3105f40, 0x3705f3f, 0x870a03f, 0xb309fc0, 0xb709fbf, 0x830a0c0, 0x192fe140, 0x196fe13f, 0x9306140, 0x170613f, 0x970a0bf, 0xb301f41, 0x192fa041, 0x182f9fc1, 0x1b2fdf41,
        17, 0x10203f, 0x101fc0, 0xfe040, 0xfe03f, 0x101fbf, 0x106040, 0x1020c0, 0xfdfc0, 0x1020bf, 0x10603f, 0x102041, 0xfdfbf, 0x105fc0, 0xfe0c0, 0xfe0bf, 0x105fbf, 0x1060c0, 0x101fc1, 0xfe041, 0x1060bf, 0x106041, 0x1020c1, 0x2fdfc1, 0x305fc1,
        0x2fe0c1, 0x3060c1, 0x70203e, 0x6fe03e, 0x701fbe, 0x70603e, 0x7020be, 0x6fdfbe, 0x3101f40, 0x3701f3f, 0x180fa040, 0x186fa03f, 0x6fe0be, 0x705fbe, 0x30fdf40, 0x1b0f9fc0, 0x186f9fbf, 0x1b6fdf3f, 0x3105f40, 0x3705f3f, 0x97060be, 0x830a040,
        0x870a03f, 0x1302140, 0x180fa0c0, 0x186fa0bf, 0x170213f, 0x192fe140, 0x192fa041, 0x3301f41, 0xb309fc0, 0xb709fbf, 0x850a0c0, 0x9506140, 0x196fe13f, 0x182f9fc1, 0x1b2fdf41, 0xb305f41, 0x12302042,
        16, 0x10203f, 0x101fc0, 0xfe040, 0x102041, 0x1020c0, 0x106040, 0x101fbf, 0xfe03f, 0xfdfc0, 0x101fc1, 0x105fc0, 0x10603f, 0x1020bf, 0xfe0c0, 0xfe041, 0xfdfbf, 0x1020c1, 0x106041, 0x1060c0, 0x105fbf, 0xfe0bf, 0xfdfc1, 0x105fc1, 0x1060bf,
        0xfe0c1, 0x83060c1, 0x70203e, 0x3101f40, 0x180fa040, 0x180fa03f, 0x186fe03e, 0x701fbe, 0x3701f3f, 0x30fdf40, 0x1b0f9fc0, 0x180fa041, 0x180fa0c0, 0x7020be, 0x70603e, 0x3105f40, 0xb101f41, 0x9302042, 0x1102140, 0x930a040, 0x6fdfbe, 0x36fdf3f,
        0x1b6f9fbf, 0x190fa0bf, 0x196fe0be, 0x170213f, 0x196fe140, 0x182f9fc1, 0x1b2fdf41, 0xb301fc2, 0x1a2fe042, 0x192fa0c1, 0x8705fbe, 0xb705f3f, 0xb309fc0, 0xa70a03f, 0x97060be, 0x9706140, 0x11302141
};

CELLBASE::CELLBASE(LD max_len_sq) :
        current_vertices(init_vertices), current_vertex_order(init_vertex_order), current_delete_size(init_delete_size), current_delete2_size(init_delete2_size), current_xsearch_size(init_xsearch_size),
        ed(new int *[current_vertices]), nu(new int[current_vertices]), mask(new unsigned int[current_vertices]), pts(new LD[current_vertices << 2]), tol(tolerance * max_len_sq),
        big_tol(big_tolerance_fac * tol), mem(new int[current_vertex_order]), mec(new int[current_vertex_order]), mep(new int *[current_vertex_order]), ds(new int[current_delete_size]),
        stacke(ds + current_delete_size), ds2(new int[current_delete2_size]), stacke2(ds2 + current_delete2_size), xse(new int[current_xsearch_size]), stacke3(xse + current_xsearch_size), maskc(0) {
    int i;
    for (i = 0; i < current_vertices; i++) mask[i] = 0;
    for (i = 0; i < 3; i++) {
        mem[i] = init_n_vertices;
        mec[i] = 0;
        mep[i] = new int[init_n_vertices * ((i << 1) + 1)];
    }
    mem[3] = init_3_vertices;
    mec[3] = 0;
    mep[3] = new int[init_3_vertices * 7];
    for (i = 4; i < current_vertex_order; i++) {
        mem[i] = init_n_vertices;
        mec[i] = 0;
        mep[i] = new int[init_n_vertices * ((i << 1) + 1)];
    }
}

CELLBASE::~CELLBASE() {
    for (int i = current_vertex_order - 1; i >= 0; i--) if (mem[i] > 0) delete[] mep[i];
    delete[] xse;
    delete[] ds2;
    delete[] ds;
    delete[] mep;
    delete[] mec;
    delete[] mem;
    delete[] pts;
    delete[] mask;
    delete[] nu;
    delete[] ed;
}

template<class C>
void CELLBASE::check_memory_for_copy(C &vc, CELLBASE *vb) {
    while (current_vertex_order < vb->current_vertex_order) add_memory_vorder(vc);
    for (int i = 0; i < current_vertex_order; i++) while (mem[i] < vb->mec[i]) add_memory(vc, i);
    while (current_vertices < vb->p) add_memory_vertices(vc);
}

void CELLBASE::copy(CELLBASE *vb) {
    int i, j;
    p = vb->p;
    up = 0;
    for (i = 0; i < current_vertex_order; i++) {
        mec[i] = vb->mec[i];
        for (j = 0; j < mec[i] * (2 * i + 1); j++) mep[i][j] = vb->mep[i][j];
        for (j = 0; j < mec[i] * (2 * i + 1); j += 2 * i + 1) ed[mep[i][j + 2 * i]] = mep[i] + j;
    }
    for (i = 0; i < p; i++) nu[i] = vb->nu[i];
    for (i = 0; i < (p << 2); i++) pts[i] = vb->pts[i];
}

void CELLNEIGHBOR::operator=(CELL &c) {
    CELLBASE *vb = ((CELLBASE *) &c);
    check_memory_for_copy(*this, vb);
    copy(vb);
    int i, j;
    for (i = 0; i < c.current_vertex_order; i++) {
        for (j = 0; j < c.mec[i] * i; j++) mne[i][j] = 0;
        for (j = 0; j < c.mec[i]; j++) ne[c.mep[i][(2 * i + 1) * j + 2 * i]] = mne[i] + (j * i);
    }
}

void CELLNEIGHBOR::operator=(CELLNEIGHBOR &c) {
    CELLBASE *vb = ((CELLBASE *) &c);
    check_memory_for_copy(*this, vb);
    copy(vb);
    int i, j;
    for (i = 0; i < c.current_vertex_order; i++) {
        for (j = 0; j < c.mec[i] * i; j++) mne[i][j] = c.mne[i][j];
        for (j = 0; j < c.mec[i]; j++) ne[c.mep[i][(2 * i + 1) * j + 2 * i]] = mne[i] + (j * i);
    }
}

template<class C>
void CELLBASE::add_memory(C &vc, int i) {
    int s = (i << 1) + 1;
    if (mem[i] == 0) {
        vc.n_allocate(i, init_n_vertices);
        mep[i] = new int[init_n_vertices * s];
        mem[i] = init_n_vertices;
    } else {
        int j = 0, k, *l;
        mem[i] <<= 1;
        l = new int[s * mem[i]];
        int m = 0;
        vc.n_allocate_aux1(i);
        while (j < s * mec[i]) {
            k = mep[i][j + (i << 1)];
            if (k >= 0) {
                ed[k] = l + j;
                vc.n_set_to_aux1_offset(k, m);
            } else {
                int *dsp;
                for (dsp = ds2; dsp < stackp2; dsp++) {
                    if (ed[*dsp] == mep[i] + j) {
                        ed[*dsp] = l + j;
                        vc.n_set_to_aux1_offset(*dsp, m);
                        break;
                    }
                }
                if (dsp == stackp2) {
                    for (dsp = xse; dsp < stackp3; dsp++) {
                        if (ed[*dsp] == mep[i] + j) {
                            ed[*dsp] = l + j;
                            vc.n_set_to_aux1_offset(*dsp, m);
                            break;
                        }
                    }
                }
            }
            for (k = 0; k < s; k++, j++) l[j] = mep[i][j];
            for (k = 0; k < i; k++, m++) vc.n_copy_to_aux1(i, m);
        }
        delete[] mep[i];
        mep[i] = l;
        vc.n_switch_to_aux1(i);
    }
}

template<class C>
void CELLBASE::add_memory_vertices(C &vc) {
    int i = (current_vertices << 1), j, **pp, *pnu;
    unsigned int *pmask;
    LD *ppts;
    pp = new int *[i];
    for (j = 0; j < current_vertices; j++) pp[j] = ed[j];
    delete[] ed;
    ed = pp;
    vc.n_add_memory_vertices(i);
    pnu = new int[i];
    for (j = 0; j < current_vertices; j++) pnu[j] = nu[j];
    delete[] nu;
    nu = pnu;
    pmask = new unsigned int[i];
    for (j = 0; j < current_vertices; j++) pmask[j] = mask[j];
    while (j < i) pmask[j++] = 0;
    delete[] mask;
    mask = pmask;
    ppts = new LD[i << 2];
    for (j = 0; j < (current_vertices << 2); j++) ppts[j] = pts[j];
    delete[] pts;
    pts = ppts;
    current_vertices = i;
}

template<class C>
void CELLBASE::add_memory_vorder(C &vc) {
    int i = (current_vertex_order << 1), j, *p1, **p2;
    p1 = new int[i];
    for (j = 0; j < current_vertex_order; j++) p1[j] = mem[j];
    while (j < i) p1[j++] = 0;
    delete[] mem;
    mem = p1;
    p2 = new int *[i];
    for (j = 0; j < current_vertex_order; j++) p2[j] = mep[j];
    delete[] mep;
    mep = p2;
    p1 = new int[i];
    for (j = 0; j < current_vertex_order; j++) p1[j] = mec[j];
    while (j < i) p1[j++] = 0;
    delete[] mec;
    mec = p1;
    vc.n_add_memory_vorder(i);
    current_vertex_order = i;
}

void CELLBASE::add_memory_ds() {
    current_delete_size <<= 1;
    int *dsn = new int[current_delete_size], *dsnp = dsn, *dsp = ds;
    while (dsp < stackp) *(dsnp++) = *(dsp++);
    delete[] ds;
    ds = dsn;
    stackp = dsnp;
    stacke = ds + current_delete_size;
}

void CELLBASE::add_memory_ds2() {
    current_delete2_size <<= 1;
    int *dsn = new int[current_delete2_size], *dsnp = dsn, *dsp = ds2;
    while (dsp < stackp2) *(dsnp++) = *(dsp++);
    delete[] ds2;
    ds2 = dsn;
    stackp2 = dsnp;
    stacke2 = ds2 + current_delete2_size;
}

void CELLBASE::add_memory_xse() {
    current_xsearch_size <<= 1;
    int *dsn = new int[current_xsearch_size], *dsnp = dsn, *dsp = xse;
    while (dsp < stackp3) *(dsnp++) = *(dsp++);
    delete[] xse;
    xse = dsn;
    stackp3 = dsnp;
    stacke3 = xse + current_xsearch_size;
}

void CELLBASE::init_base(LD xmin, LD xmax, LD ymin, LD ymax, LD zmin, LD zmax) {
    for (int i = 0; i < current_vertex_order; i++) mec[i] = 0;
    up = 0;
    mec[3] = p = 8;
    xmin *= 2;
    xmax *= 2;
    ymin *= 2;
    ymax *= 2;
    zmin *= 2;
    zmax *= 2;
    *pts = xmin;
    pts[1] = ymin;
    pts[2] = zmin;
    pts[4] = xmax;
    pts[5] = ymin;
    pts[6] = zmin;
    pts[8] = xmin;
    pts[9] = ymax;
    pts[10] = zmin;
    pts[12] = xmax;
    pts[13] = ymax;
    pts[14] = zmin;
    pts[16] = xmin;
    pts[17] = ymin;
    pts[18] = zmax;
    pts[20] = xmax;
    pts[21] = ymin;
    pts[22] = zmax;
    pts[24] = xmin;
    pts[25] = ymax;
    pts[26] = zmax;
    pts[28] = xmax;
    pts[29] = ymax;
    pts[30] = zmax;
    int *q = mep[3];
    *q = 1;
    q[1] = 4;
    q[2] = 2;
    q[3] = 2;
    q[4] = 1;
    q[5] = 0;
    q[6] = 0;
    q[7] = 3;
    q[8] = 5;
    q[9] = 0;
    q[10] = 2;
    q[11] = 1;
    q[12] = 0;
    q[13] = 1;
    q[14] = 0;
    q[15] = 6;
    q[16] = 3;
    q[17] = 2;
    q[18] = 1;
    q[19] = 0;
    q[20] = 2;
    q[21] = 2;
    q[22] = 7;
    q[23] = 1;
    q[24] = 2;
    q[25] = 1;
    q[26] = 0;
    q[27] = 3;
    q[28] = 6;
    q[29] = 0;
    q[30] = 5;
    q[31] = 2;
    q[32] = 1;
    q[33] = 0;
    q[34] = 4;
    q[35] = 4;
    q[36] = 1;
    q[37] = 7;
    q[38] = 2;
    q[39] = 1;
    q[40] = 0;
    q[41] = 5;
    q[42] = 7;
    q[43] = 2;
    q[44] = 4;
    q[45] = 2;
    q[46] = 1;
    q[47] = 0;
    q[48] = 6;
    q[49] = 5;
    q[50] = 3;
    q[51] = 6;
    q[52] = 2;
    q[53] = 1;
    q[54] = 0;
    q[55] = 7;
    *ed = q;
    ed[1] = q + 7;
    ed[2] = q + 14;
    ed[3] = q + 21;
    ed[4] = q + 28;
    ed[5] = q + 35;
    ed[6] = q + 42;
    ed[7] = q + 49;
    *nu = nu[1] = nu[2] = nu[3] = nu[4] = nu[5] = nu[6] = nu[7] = 3;
}

inline bool CELLBASE::search_for_outside_edge(int &upp) {
    int i, lp, lw, *j = stackp2, sc2 = stackp2 - ds2;
    LD l;
    *(stackp2++) = upp;
    while (j < stackp2) {
        upp = *(j++);
        for (i = 0; i < nu[upp]; i++) {
            lp = ed[upp][i];
            lw = m_test(lp, l);
            if (lw == 0) {
                stackp2 = ds2 + sc2;
                return true;
            } else if (lw == 1) add_to_stack(sc2, lp);
        }
    }
    stackp2 = ds2 + sc2;
    return false;
}

inline void CELLBASE::add_to_stack(int sc2, int lp) {
    for (int *k = ds2 + sc2; k < stackp2; k++) if (*k == lp) return;
    if (stackp2 == stacke2) add_memory_ds2();
    *(stackp2++) = lp;
}

inline bool CELLBASE::search_upward(unsigned int &uw, int &lp, int &ls, int &us, LD &l, LD &u) {
    int vs;
    lp = up;
    l = u;
    for (ls = 0; ls < nu[lp]; ls++) {
        up = ed[lp][ls];
        uw = m_test(up, u);
        if (u > l) break;
    }
    if (ls == nu[lp])
        if (definite_max(lp, ls, l, u, uw)) {
            up = lp;
            return false;
        }
    while (uw == 0) {
        vs = ed[lp][nu[lp] + ls];
        lp = up;
        l = u;
        for (ls = 0; ls < nu[lp]; ls++) {
            if (ls == vs) continue;
            up = ed[lp][ls];
            uw = m_test(up, u);
            if (u > l) break;
        }
        if (ls == nu[lp] && definite_max(lp, ls, l, u, uw)) {
            up = lp;
            return false;
        }
    }
    us = ed[lp][nu[lp] + ls];
    return true;
}

bool CELLBASE::definite_max(int &lp, int &ls, LD &l, LD &u, unsigned int &uw) {
    int tp = lp, ts, qp = 0;
    unsigned int qw;
    LD q;
    for (ts = 0; ts < nu[tp]; ts++) {
        qp = ed[tp][ts];
        m_test(qp, q);
        if (q > l - big_tol) break;
    }
    if (ts == nu[tp]) return true;
    int *stackpp = ds + 1;
    flip(lp);
    flip(qp);
    *ds = qp;
    ts++;
    while (ts < nu[tp]) {
        qp = ed[tp][ts];
        m_test(qp, q);
        if (q > l - big_tol) {
            if (stackpp == stacke) add_memory_ds();
            *(stackpp++) = up;
            flip(up);
        }
        ts++;
    }
    int *spp = ds;
    while (spp < stackpp) {
        tp = *(spp++);
        for (ts = 0; ts < nu[tp]; ts++) {
            qp = ed[tp][ts];
            if (ed[qp][nu[qp] << 1] < 0) continue;
            qw = m_test(qp, q);
            if (q > l) {
                flip(lp);
                lp = tp;
                ls = ts;
                m_test(lp, l);
                up = qp;
                uw = qw;
                u = q;
                while (stackpp > ds) flip(*(--stackpp));
                return false;
            }
            if (q > l - big_tol) {
                if (stackpp == stacke) {
                    int nn = stackpp - spp;
                    add_memory_ds();
                    spp = stackpp - nn;
                }
                *(stackpp++) = qp;
                flip(qp);
            }
        }
    }
    flip(lp);
    while (stackpp > ds) flip(*(--stackpp));
    return true;
}

inline bool CELLBASE::search_downward(unsigned int &lw, int &lp, int &ls, int &us, LD &l, LD &u) {
    int vs;
    for (us = 0; us < nu[up]; us++) {
        lp = ed[up][us];
        lw = m_test(lp, l);
        if (u > l) break;
    }
    if (us == nu[up]) if (definite_min(lp, us, l, u, lw)) return false;
    while (lw == 2) {
        vs = ed[up][nu[up] + us];
        up = lp;
        u = l;
        for (us = 0; us < nu[up]; us++) {
            if (us == vs) continue;
            lp = ed[up][us];
            lw = m_test(lp, l);
            if (u > l) break;
        }
        if (us == nu[up] && definite_min(lp, us, l, u, lw)) return false;
    }
    ls = ed[up][nu[up] + us];
    return true;
}

bool CELLBASE::definite_min(int &lp, int &us, LD &l, LD &u, unsigned int &lw) {
    int tp = up, ts, qp = 0;
    unsigned int qw;
    LD q;
    for (ts = 0; ts < nu[tp]; ts++) {
        qp = ed[tp][ts];
        m_test(qp, q);
        if (q < u + big_tol) break;
    }
    if (ts == nu[tp]) return true;
    int *stackpp = ds + 1;
    flip(up);
    flip(qp);
    *ds = qp;
    ts++;
    while (ts < nu[tp]) {
        qp = ed[tp][ts];
        m_test(qp, q);
        if (q < u + big_tol) {
            if (stackpp == stacke) add_memory_ds();
            *(stackpp++) = lp;
            flip(lp);
        }
        ts++;
    }
    int *spp = ds;
    while (spp < stackpp) {
        tp = *(spp++);
        for (ts = 0; ts < nu[tp]; ts++) {
            qp = ed[tp][ts];
            if (ed[qp][nu[qp] << 1] < 0) continue;
            qw = m_test(qp, q);
            if (q < u) {
                flip(up);
                up = tp;
                us = ts;
                m_test(up, u);
                lp = qp;
                lw = qw;
                l = q;
                while (stackpp > ds) flip(*(--stackpp));
                return false;
            }
            if (q < u + big_tol) {
                if (stackpp == stacke) {
                    int nn = stackpp - spp;
                    add_memory_ds();
                    spp = stackpp - nn;
                }
                *(stackpp++) = qp;
                flip(qp);
            }
        }
    }
    flip(up);
    while (stackpp > ds) flip(*(--stackpp));
    return true;
}

template<class C>
bool CELLBASE::nplane(C &vc, LD x, LD y, LD z, LD rsq, int p_id) {
    int i, j, lp = up, cp, qp, *dsp, us = 0, ls = 0, *edp, *edd;
    unsigned int uw, lw;
    stackp = ds;
    LD u, l = 0;
    up = 0;
    px = x;
    py = y;
    pz = z;
    prsq = rsq;
    maskc += 4;
    if (maskc < 4) reset_mask();
    uw = m_test(up, u);
    if (uw == 2) {
        if (!search_downward(lw, lp, ls, us, l, u)) return false;
        if (lw == 1) {
            up = lp;
            lp = -1;
        }
    } else if (uw == 0) {
        if (!search_upward(uw, lp, ls, us, l, u)) return true;
        if (uw == 1) lp = -1;
    } else {
        lp = -1;
    }
    stackp = ds;
    stackp2 = ds2;
    stackp3 = xse;
    int op = p;
    if (create_facet(vc, lp, ls, l, us, u, p_id)) return false;
    int k = 0;
    int xtra = 0;
    while (xse + k < stackp3) {
        lp = xse[k++];
        uw = m_test(lp, l);
        for (ls = 0; ls < nu[lp]; ls++) {
            up = ed[lp][ls];
            uw = m_test(up, u);
            if (up >= op) continue;
            if (uw == 0) {
                if (u > -big_tol && ed[up][nu[up] << 1] != -1) {
                    ed[up][nu[up] << 1] = -1;
                    if (stackp3 == stacke3) add_memory_xse();
                    *(stackp3++) = up;
                }
            } else if (uw == 1) {
                if (create_facet(vc, -1, 0, 0, 0, u, p_id)) return false;
            } else {
                us = ed[lp][nu[lp] + ls];
                m_test(lp, l);
                if (create_facet(vc, lp, ls, l, us, u, p_id)) return false;
            }
        }
        xtra++;
    }
    for (dsp = xse; dsp < stackp3; dsp++) {
        j = *dsp;
        ed[j][nu[j] << 1] = j;
    }
    dsp = ds;
    while (dsp < stackp) {
        j = *dsp;
        if (ed[j][nu[j]] != -1) {
            ed[j][nu[j]] = -1;
            dsp++;
        } else *dsp = *(--stackp);
    }
    for (dsp = ds2; dsp < stackp2; dsp++) {
        j = *dsp;
        ed[j][nu[j] << 1] = j;
        if (ed[j][nu[j]] != -1) {
            ed[j][nu[j]] = -1;
            if (stackp == stacke) add_memory_ds();
            *(stackp++) = j;
        }
    }
    for (dsp = ds; dsp < stackp; dsp++) {
        cp = *dsp;
        for (edp = ed[cp]; edp < ed[cp] + nu[cp]; edp++) {
            qp = *edp;
            if (qp != -1 && ed[qp][nu[qp]] != -1) {
                if (stackp == stacke) {
                    int dis = stackp - dsp;
                    add_memory_ds();
                    dsp = ds + dis;
                }
                *(stackp++) = qp;
                ed[qp][nu[qp]] = -1;
            }
        }
    }
    up = 0;
    while (stackp > ds) {
        --p;
        while (ed[p][nu[p]] == -1) {
            j = nu[p];
            edp = ed[p];
            edd = (mep[j] + ((j << 1) + 1) * --mec[j]);
            while (edp < ed[p] + (j << 1) + 1) *(edp++) = *(edd++);
            vc.n_set_aux2_copy(p, j);
            vc.n_copy_pointer(ed[p][(j << 1)], p);
            ed[ed[p][(j << 1)]] = ed[p];
            --p;
        }
        up = *(--stackp);
        if (up < p) {
            pts[(up << 2)] = pts[(p << 2)];
            pts[(up << 2) + 1] = pts[(p << 2) + 1];
            pts[(up << 2) + 2] = pts[(p << 2) + 2];
            j = nu[up];
            edp = ed[up];
            edd = (mep[j] + ((j << 1) + 1) * --mec[j]);
            while (edp < ed[up] + (j << 1) + 1) *(edp++) = *(edd++);
            vc.n_set_aux2_copy(up, j);
            vc.n_copy_pointer(ed[up][j << 1], up);
            vc.n_copy_pointer(up, p);
            ed[ed[up][j << 1]] = ed[up];
            ed[up] = ed[p];
            nu[up] = nu[p];
            for (i = 0; i < nu[up]; i++) ed[ed[up][i]][ed[up][nu[up] + i]] = up;
            ed[up][nu[up] << 1] = up;
        } else up = p++;
    }
    return collapse_order2(vc);
}

template<class C>
bool CELLBASE::create_facet(C &vc, int lp, int ls, LD l, int us, LD u, int p_id) {
    int i, j, k, qp, qs, iqs, cp, cs, rp, *edp, *edd;
    unsigned int lw, qw;
    bool new_LD_edge = false, LD_edge = false;
    LD q, r;
    if (p == current_vertices) add_memory_vertices(vc);
    if (lp == -1) {
        if (!search_for_outside_edge(up)) return true;
        pts[(p << 2)] = pts[(up << 2)];
        pts[(p << 2) + 1] = pts[(up << 2) + 1];
        pts[(p << 2) + 2] = pts[(up << 2) + 2];
        i = 0;
        lp = *ed[up];
        lw = m_testx(lp, l);
        if (lw != 0) {
            unsigned int rw = lw;
            do {
                i++;
                if (i == nu[up]) return true;
                lp = ed[up][i];
                lw = m_testx(lp, l);
            } while (lw != 0);
            j = i + 1;
            while (j < nu[up]) {
                lp = ed[up][j];
                lw = m_testx(lp, l);
                if (lw != 0) break;
                j++;
            }
            if (j == nu[up] && i == 1 && rw == 1) {
                nu[p] = nu[up];
                LD_edge = true;
            } else nu[p] = j - i + 2;
            k = 1;
            while (nu[p] >= current_vertex_order) add_memory_vorder(vc);
            if (mec[nu[p]] == mem[nu[p]]) add_memory(vc, nu[p]);
            vc.n_set_pointer(p, nu[p]);
            ed[p] = mep[nu[p]] + ((nu[p] << 1) + 1) * mec[nu[p]]++;
            ed[p][nu[p] << 1] = p;
            us = cycle_down(i, up);
            while (i < j) {
                qp = ed[up][i];
                qs = ed[up][nu[up] + i];
                vc.n_copy(p, k, up, i);
                ed[p][k] = qp;
                ed[p][nu[p] + k] = qs;
                ed[qp][qs] = p;
                ed[qp][nu[qp] + qs] = k;
                ed[up][i] = -1;
                i++;
                k++;
            }
            qs = i == nu[up] ? 0 : i;
        } else {
            i = nu[up] - 1;
            lp = ed[up][i];
            lw = m_testx(lp, l);
            while (lw == 0) {
                i--;
                if (i == 0) return false;
                lp = ed[up][i];
                lw = m_testx(lp, l);
            }
            j = 1;
            qp = ed[up][j];
            qw = m_testx(qp, q);
            while (qw == 0) {
                j++;
                qp = ed[up][j];
                qw = m_testx(qp, l);
            }
            if (i == j && qw == 1) {
                LD_edge = true;
                nu[p] = nu[up];
            } else {
                nu[p] = nu[up] - i + j + 1;
            }
            k = 1;
            while (nu[p] >= current_vertex_order) add_memory_vorder(vc);
            if (mec[nu[p]] == mem[nu[p]]) add_memory(vc, nu[p]);
            vc.n_set_pointer(p, nu[p]);
            ed[p] = mep[nu[p]] + ((nu[p] << 1) + 1) * mec[nu[p]]++;
            ed[p][nu[p] << 1] = p;
            us = i++;
            while (i < nu[up]) {
                qp = ed[up][i];
                qs = ed[up][nu[up] + i];
                vc.n_copy(p, k, up, i);
                ed[p][k] = qp;
                ed[p][nu[p] + k] = qs;
                ed[qp][qs] = p;
                ed[qp][nu[qp] + qs] = k;
                ed[up][i] = -1;
                i++;
                k++;
            }
            i = 0;
            while (i < j) {
                qp = ed[up][i];
                qs = ed[up][nu[up] + i];
                vc.n_copy(p, k, up, i);
                ed[p][k] = qp;
                ed[p][nu[p] + k] = qs;
                ed[qp][qs] = p;
                ed[qp][nu[qp] + qs] = k;
                ed[up][i] = -1;
                i++;
                k++;
            }
            qs = j;
        }
        if (!LD_edge) {
            vc.n_copy(p, k, up, qs);
            vc.n_set(p, 0, p_id);
        } else vc.n_copy(p, 0, up, qs);
        if (stackp2 == stacke2) add_memory_ds2();
        *(stackp2++) = up;
        cs = k;
        qp = up;
        q = u;
        i = ed[up][us];
        us = ed[up][nu[up] + us];
        up = i;
        ed[qp][nu[qp] << 1] = -p;
    } else {
        if (stackp == stacke) add_memory_ds();
        *(stackp++) = up;
        r = u / (u - l);
        l = 1 - r;
        pts[p << 2] = pts[lp << 2] * r + pts[up << 2] * l;
        pts[(p << 2) + 1] = pts[(lp << 2) + 1] * r + pts[(up << 2) + 1] * l;
        pts[(p << 2) + 2] = pts[(lp << 2) + 2] * r + pts[(up << 2) + 2] * l;
        nu[p] = 3;
        if (mec[3] == mem[3]) add_memory(vc, 3);
        vc.n_set_pointer(p, 3);
        vc.n_set(p, 0, p_id);
        vc.n_copy(p, 1, up, us);
        vc.n_copy(p, 2, lp, ls);
        ed[p] = mep[3] + 7 * mec[3]++;
        ed[p][6] = p;
        ed[up][us] = -1;
        ed[lp][ls] = p;
        ed[lp][nu[lp] + ls] = 1;
        ed[p][1] = lp;
        ed[p][nu[p] + 1] = ls;
        cs = 2;
        qs = cycle_up(us, up);
        qp = up;
        q = u;
    }
    cp = p;
    rp = p;
    p++;
    while (qp != up || qs != us) {
        lp = ed[qp][qs];
        lw = m_testx(lp, l);
        if (lw == 2) {
            qs = cycle_up(ed[qp][nu[qp] + qs], lp);
            qp = lp;
            q = l;
            if (stackp == stacke) add_memory_ds();
            *(stackp++) = qp;
        } else if (lw == 0) {
            if (p == current_vertices) add_memory_vertices(vc);
            r = q / (q - l);
            l = 1 - r;
            pts[p << 2] = pts[lp << 2] * r + pts[qp << 2] * l;
            pts[(p << 2) + 1] = pts[(lp << 2) + 1] * r + pts[(qp << 2) + 1] * l;
            pts[(p << 2) + 2] = pts[(lp << 2) + 2] * r + pts[(qp << 2) + 2] * l;
            nu[p] = 3;
            if (mec[3] == mem[3]) add_memory(vc, 3);
            ls = ed[qp][qs + nu[qp]];
            vc.n_set_pointer(p, 3);
            vc.n_set(p, 0, p_id);
            vc.n_copy(p, 1, qp, qs);
            vc.n_copy(p, 2, lp, ls);
            ed[p] = mep[3] + 7 * mec[3]++;
            *ed[p] = cp;
            ed[p][1] = lp;
            ed[p][3] = cs;
            ed[p][4] = ls;
            ed[p][6] = p;
            ed[lp][ls] = p;
            ed[lp][nu[lp] + ls] = 1;
            ed[cp][cs] = p;
            ed[cp][nu[cp] + cs] = 0;
            ed[qp][qs] = -1;
            qs = cycle_up(qs, qp);
            cp = p++;
            cs = 2;
        } else {
            if (p == current_vertices) add_memory_vertices(vc);
            k = LD_edge ? 0 : 1;
            qs = ed[qp][nu[qp] + qs];
            qp = lp;
            iqs = qs;
            do {
                k++;
                qs = cycle_up(qs, qp);
                lp = ed[qp][qs];
                lw = m_testx(lp, l);
            } while (lw == 0);
            j = -ed[qp][nu[qp] << 1];
            if (qp == up && qs == us) {
                new_LD_edge = false;
                if (j > 0) k += nu[j];
            } else {
                if (j > 0) {
                    k += nu[j];
                    if (lw == 1) {
                        i = -ed[lp][nu[lp] << 1];
                        if (i > 0) {
                            if (ed[i][nu[i] - 1] == j) {
                                new_LD_edge = true;
                                k -= 1;
                            } else new_LD_edge = false;
                        } else {
                            if (j == rp && lp == up && ed[qp][nu[qp] + qs] == us) {
                                new_LD_edge = true;
                                k -= 1;
                            } else new_LD_edge = false;
                        }
                    } else new_LD_edge = false;
                } else {
                    if (lw == 1) {
                        i = -ed[lp][nu[lp] << 1];
                        if (i == cp) {
                            new_LD_edge = true;
                            k -= 1;
                        } else new_LD_edge = false;
                    } else new_LD_edge = false;
                }
            }
            while (k >= current_vertex_order) add_memory_vorder(vc);
            if (mec[k] == mem[k]) add_memory(vc, k);
            if (j > 0) {
                if (nu[j] != k) {
                    vc.n_set_aux1(k);
                    edp = mep[k] + ((k << 1) + 1) * mec[k]++;
                    i = 0;
                    while (i < nu[j]) {
                        vc.n_copy_aux1(j, i);
                        edp[i] = ed[j][i];
                        edp[k + i] = ed[j][nu[j] + i];
                        i++;
                    }
                    edp[k << 1] = j;
                    edd = mep[nu[j]] + ((nu[j] << 1) + 1) * --mec[nu[j]];
                    if (edd != ed[j]) {
                        for (int lll = 0; lll <= (nu[j] << 1); lll++) ed[j][lll] = edd[lll];
                        vc.n_set_aux2_copy(j, nu[j]);
                        vc.n_copy_pointer(edd[nu[j] << 1], j);
                        ed[edd[nu[j] << 1]] = ed[j];
                    }
                    vc.n_set_to_aux1(j);
                    ed[j] = edp;
                } else i = nu[j];
            } else {
                vc.n_set_pointer(p, k);
                ed[p] = mep[k] + ((k << 1) + 1) * mec[k]++;
                ed[p][k << 1] = p;
                if (stackp2 == stacke2) add_memory_ds2();
                *(stackp2++) = qp;
                pts[p << 2] = pts[qp << 2];
                pts[(p << 2) + 1] = pts[(qp << 2) + 1];
                pts[(p << 2) + 2] = pts[(qp << 2) + 2];
                ed[qp][nu[qp] << 1] = -p;
                j = p++;
                i = 0;
            }
            nu[j] = k;
            if (!LD_edge) {
                ed[j][i] = cp;
                ed[j][nu[j] + i] = cs;
                vc.n_set(j, i, p_id);
                ed[cp][cs] = j;
                ed[cp][nu[cp] + cs] = i;
                i++;
            }
            qs = iqs;
            while (i < (new_LD_edge ? k : k - 1)) {
                qs = cycle_up(qs, qp);
                lp = ed[qp][qs];
                ls = ed[qp][nu[qp] + qs];
                vc.n_copy(j, i, qp, qs);
                ed[j][i] = lp;
                ed[j][nu[j] + i] = ls;
                ed[lp][ls] = j;
                ed[lp][nu[lp] + ls] = i;
                ed[qp][qs] = -1;
                i++;
            }
            qs = cycle_up(qs, qp);
            cs = i;
            cp = j;
            vc.n_copy(j, new_LD_edge ? 0 : cs, qp, qs);
            LD_edge = new_LD_edge;
        }
    }
    ed[cp][cs] = rp;
    *ed[rp] = cp;
    ed[cp][nu[cp] + cs] = 0;
    ed[rp][nu[rp]] = cs;
    return false;
}

template<class C>
inline bool CELLBASE::collapse_order2(C &vc) {
    if (!collapse_order1(vc)) return false;
    int a, b, i, j, k, l;
    while (mec[2] > 0) {
        i = --mec[2];
        j = mep[2][5 * i];
        k = mep[2][5 * i + 1];
        if (j == k) {
            return false;
        }
        for (l = 0; l < nu[j]; l++) {
            if (ed[j][l] == k) break;
        }
        a = mep[2][5 * i + 2];
        b = mep[2][5 * i + 3];
        i = mep[2][5 * i + 4];
        if (l == nu[j]) {
            ed[j][a] = k;
            ed[k][b] = j;
            ed[j][nu[j] + a] = b;
            ed[k][nu[k] + b] = a;
        } else {
            if (!delete_connection(vc, j, a, false)) return false;
            if (!delete_connection(vc, k, b, true)) return false;
        }
        --p;
        if (up == i) up = 0;
        if (p != i) {
            if (up == p) up = i;
            pts[i << 2] = pts[p << 2];
            pts[(i << 2) + 1] = pts[(p << 2) + 1];
            pts[(i << 2) + 2] = pts[(p << 2) + 2];
            for (k = 0; k < nu[p]; k++) ed[ed[p][k]][ed[p][nu[p] + k]] = i;
            vc.n_copy_pointer(i, p);
            ed[i] = ed[p];
            nu[i] = nu[p];
            ed[i][nu[i] << 1] = i;
        }
        if (!collapse_order1(vc)) return false;
    }
    return true;
}

template<class C>
bool CELLBASE::collapse_order1(C &vc) {
    int i, j, k;
    while (mec[1] > 0) {
        up = 0;
        i = --mec[1];
        j = mep[1][3 * i];
        k = mep[1][3 * i + 1];
        i = mep[1][3 * i + 2];
        if (!delete_connection(vc, j, k, false)) return false;
        --p;
        if (up == i) up = 0;
        if (p != i) {
            if (up == p) up = i;
            pts[i << 2] = pts[p << 2];
            pts[(i << 2) + 1] = pts[(p << 2) + 1];
            pts[(i << 2) + 2] = pts[(p << 2) + 2];
            for (k = 0; k < nu[p]; k++) ed[ed[p][k]][ed[p][nu[p] + k]] = i;
            vc.n_copy_pointer(i, p);
            ed[i] = ed[p];
            nu[i] = nu[p];
            ed[i][nu[i] << 1] = i;
        }
    }
    return true;
}

template<class C>
bool CELLBASE::delete_connection(C &vc, int j, int k, bool hand) {
    int q = hand ? k : cycle_up(k, j), i = nu[j] - 1, l, *edp, *edd, m;
    if (mec[i] == mem[i]) add_memory(vc, i);
    vc.n_set_aux1(i);
    for (l = 0; l < q; l++) vc.n_copy_aux1(j, l);
    while (l < i) {
        vc.n_copy_aux1_shift(j, l);
        l++;
    }
    edp = mep[i] + ((i << 1) + 1) * mec[i]++;
    edp[i << 1] = j;
    for (l = 0; l < k; l++) {
        edp[l] = ed[j][l];
        edp[l + i] = ed[j][l + nu[j]];
    }
    while (l < i) {
        m = ed[j][l + 1];
        edp[l] = m;
        k = ed[j][l + nu[j] + 1];
        edp[l + i] = k;
        ed[m][nu[m] + k]--;
        l++;
    }
    edd = mep[nu[j]] + ((nu[j] << 1) + 1) * --mec[nu[j]];
    for (l = 0; l <= (nu[j] << 1); l++) ed[j][l] = edd[l];
    vc.n_set_aux2_copy(j, nu[j]);
    vc.n_copy_pointer(edd[nu[j] << 1], j);
    vc.n_set_to_aux1(j);
    ed[edd[nu[j] << 1]] = ed[j];
    ed[j] = edp;
    nu[j] = i;
    return true;
}

LD CELLBASE::volume() {
    LD vol = 0, ux, uy, uz, vx, vy, vz, wx, wy, wz;
    int i, j, k, l, m, n;
    for (i = 1; i < p; i++) {
        ux = *pts - pts[i << 2];
        uy = pts[1] - pts[(i << 2) + 1];
        uz = pts[2] - pts[(i << 2) + 2];
        for (j = 0; j < nu[i]; j++) {
            k = ed[i][j];
            if (k >= 0) {
                ed[i][j] = -1 - k;
                l = cycle_up(ed[i][nu[i] + j], k);
                vx = pts[k << 2] - *pts;
                vy = pts[(k << 2) + 1] - pts[1];
                vz = pts[(k << 2) + 2] - pts[2];
                m = ed[k][l];
                ed[k][l] = -1 - m;
                while (m != i) {
                    n = cycle_up(ed[k][nu[k] + l], m);
                    wx = pts[(m << 2)] - *pts;
                    wy = pts[(m << 2) + 1] - pts[1];
                    wz = pts[(m << 2) + 2] - pts[2];
                    vol += ux * vy * wz + uy * vz * wx + uz * vx * wy - uz * vy * wx - uy * vx * wz - ux * vz * wy;
                    k = m;
                    l = n;
                    vx = wx;
                    vy = wy;
                    vz = wz;
                    m = ed[k][l];
                    ed[k][l] = -1 - m;
                }
            }
        }
    }
    reset_edges();
    return vol / 48.0;
}

LD CELLBASE::max_radius_squared() const {
    LD r, s, *ptsp = pts + 4, *ptse = pts + (p << 2);
    r = *pts * (*pts) + pts[1] * pts[1] + pts[2] * pts[2];
    while (ptsp < ptse) {
        s = *ptsp * (*ptsp);
        ptsp++;
        s += *ptsp * (*ptsp);
        ptsp++;
        s += *ptsp * (*ptsp);
        ptsp += 2;
        if (s > r) r = s;
    }
    return r;
}

inline void CELLBASE::reset_edges() const {
    int i, j;
    for (i = 0; i < p; i++) for (j = 0; j < nu[i]; j++) ed[i][j] = -1 - ed[i][j];
}

inline unsigned int CELLBASE::m_test(int n, LD &ans) {
    if (mask[n] >= maskc) {
        ans = pts[4 * n + 3];
        return mask[n] & 3;
    }
    return m_calc(n, ans);
}

unsigned int CELLBASE::m_calc(int n, LD &ans) const {
    LD *pp = pts + 4 * n;
    ans = *(pp++) * px;
    ans += *(pp++) * py;
    ans += *(pp++) * pz - prsq;
    *pp = ans;
    unsigned int maskr = ans < -tol ? 0 : (ans > tol ? 2 : 1);
    mask[n] = maskc | maskr;
    return maskr;
}

inline unsigned int CELLBASE::m_testx(int n, LD &ans) {
    unsigned int maskr;
    if (mask[n] >= maskc) {
        ans = pts[4 * n + 3];
        maskr = mask[n] & 3;
    } else maskr = m_calc(n, ans);
    if (maskr == 0 && ans > -big_tol && ed[n][nu[n] << 1] != -1) {
        ed[n][nu[n] << 1] = -1;
        if (stackp3 == stacke3) add_memory_xse();
        *(stackp3++) = n;
    }
    return maskr;
}

bool CELLBASE::plane_intersects(LD x, LD y, LD z, LD rsq) {
    LD g = x * pts[up << 2] + y * pts[(up << 2) + 1] + z * pts[(up << 2) + 2];
    if (g < rsq) return plane_intersects_track(x, y, z, rsq, g);
    return true;
}

bool CELLBASE::plane_intersects_guess(LD x, LD y, LD z, LD rsq) {
    up = 0;
    LD g = x * pts[up << 2] + y * pts[(up << 2) + 1] + z * pts[(up << 2) + 2];
    if (g < rsq) {
        int ca = 1, cc = p >> 3, mp = 1;
        LD m;
        while (ca < cc) {
            m = x * pts[4 * mp] + y * pts[4 * mp + 1] + z * pts[4 * mp + 2];
            if (m > g) {
                if (m > rsq) return true;
                g = m;
                up = mp;
            }
            ca += mp++;
        }
        return plane_intersects_track(x, y, z, rsq, g);
    }
    return true;
}

inline bool CELLBASE::plane_intersects_track(LD x, LD y, LD z, LD rsq, LD g) const {
    for (int tp = 0; tp < p; tp++) if (x * pts[tp << 2] + y * pts[(tp << 2) + 1] + z * pts[(tp << 2) + 2] > rsq) return true;
    return false;
}

void CELLNEIGHBOR::init(LD xmin, LD xmax, LD ymin, LD ymax, LD zmin, LD zmax) {
    init_base(xmin, xmax, ymin, ymax, zmin, zmax);
    int *q = mne[3];
    *q = -5;
    q[1] = -3;
    q[2] = -1;
    q[3] = -5;
    q[4] = -2;
    q[5] = -3;
    q[6] = -5;
    q[7] = -1;
    q[8] = -4;
    q[9] = -5;
    q[10] = -4;
    q[11] = -2;
    q[12] = -6;
    q[13] = -1;
    q[14] = -3;
    q[15] = -6;
    q[16] = -3;
    q[17] = -2;
    q[18] = -6;
    q[19] = -4;
    q[20] = -1;
    q[21] = -6;
    q[22] = -2;
    q[23] = -4;
    *ne = q;
    ne[1] = q + 3;
    ne[2] = q + 6;
    ne[3] = q + 9;
    ne[4] = q + 12;
    ne[5] = q + 15;
    ne[6] = q + 18;
    ne[7] = q + 21;
}

void CELLNEIGHBOR::memory_setup() {
    int i;
    mne = new int *[current_vertex_order];
    ne = new int *[current_vertices];
    for (i = 0; i < 3; i++) mne[i] = new int[init_n_vertices * i];
    mne[3] = new int[init_3_vertices * 3];
    for (i = 4; i < current_vertex_order; i++) mne[i] = new int[init_n_vertices * i];
}

CELLNEIGHBOR::~CELLNEIGHBOR() {
    for (int i = current_vertex_order - 1; i >= 0; i--) if (mem[i] > 0) delete[] mne[i];
    delete[] mne;
    delete[] ne;
}

template bool CELLBASE::nplane(CELL &, LD, LD, LD, LD, int);

template bool CELLBASE::nplane(CELLNEIGHBOR &, LD, LD, LD, LD, int);

template void CELLBASE::check_memory_for_copy(CELL &, CELLBASE *);

template void CELLBASE::check_memory_for_copy(CELLNEIGHBOR &, CELLBASE *);

CONTAINERBASE::CONTAINERBASE(LD ax_, LD bx_, LD ay_, LD by_, LD az_, LD bz_, int nx_, int ny_, int nz_, int init_mem, int ps_)
        : BASE(nx_, ny_, nz_, (bx_ - ax_) / nx_, (by_ - ay_) / ny_, (bz_ - az_) / nz_), ax(ax_), bx(bx_), ay(ay_), by(by_), az(az_), bz(bz_),
          max_len_sq((bx - ax) * (bx - ax) + (by - ay) * (by - ay) + (bz - az) * (bz - az)), id(new int *[nxyz]), p(new LD *[nxyz]), co(new int[nxyz]), mem(new int[nxyz]), ps(ps_) {
    int l;
    for (l = 0; l < nxyz; l++) co[l] = 0;
    for (l = 0; l < nxyz; l++) mem[l] = init_mem;
    for (l = 0; l < nxyz; l++) id[l] = new int[init_mem];
    for (l = 0; l < nxyz; l++) p[l] = new LD[ps * init_mem];
}

CONTAINERBASE::~CONTAINERBASE() {
    int l;
    for (l = 0; l < nxyz; l++) delete[] p[l];
    for (l = 0; l < nxyz; l++) delete[] id[l];
    delete[] id;
    delete[] p;
    delete[] co;
    delete[] mem;
}

CONTAINER::CONTAINER(LD ax_, LD bx_, LD ay_, LD by_, LD az_, LD bz_, int nx_, int ny_, int nz_, int init_mem)
        : CONTAINERBASE(ax_, bx_, ay_, by_, az_, bz_, nx_, ny_, nz_, init_mem, 3), vc(*this, nx_, ny_, nz_) {}

void CONTAINER::put(int n, LD x, LD y, LD z) {
    int ijk;
    if (!put_locate_block(ijk, x, y, z)) return;
    id[ijk][co[ijk]] = n;
    LD *pp = p[ijk] + 3 * co[ijk]++;
    *(pp++) = x;
    *(pp++) = y;
    *pp = z;
}

bool CONTAINERBASE::put_locate_block(int &ijk, LD &x, LD &y, LD &z) {
    if (put_remap(ijk, x, y, z)) {
        if (co[ijk] == mem[ijk]) add_particle_memory(ijk);
        return true;
    }
    return false;
}

inline bool CONTAINERBASE::put_remap(int &ijk, LD &x, LD &y, LD &z) {
    ijk = step_int((x - ax) * xsp);
    if (ijk < 0 || ijk >= nx) return false;
    int j = step_int((y - ay) * ysp);
    if (j < 0 || j >= ny) return false;
    int k = step_int((z - az) * zsp);
    if (k < 0 || k >= nz) return false;
    ijk += nx * j + nxy * k;
    return true;
}

void CONTAINERBASE::add_particle_memory(int i) const {
    int l, nmem = mem[i] << 1;
    int *idp = new int[nmem];
    for (l = 0; l < co[i]; l++) idp[l] = id[i][l];
    LD *pp = new LD[ps * nmem];
    for (l = 0; l < ps * co[i]; l++) pp[l] = p[i][l];
    mem[i] = nmem;
    delete[] id[i];
    id[i] = idp;
    delete[] p[i];
    p[i] = pp;
}

vector<LD> CONTAINER::cell_volumes(int p) {
    vector<LD> result(p);
    CELL c(*this);
    LOOP vl(*this);
    if (vl.start()) do if (compute_cell(c, vl)) result[id[vl.ijk][vl.q]] = c.volume(); while (vl.inc());
    return result;
}

WALLS::WALLS() : walls(new WALL *[init_wall_size]), wep(walls) {}

WALLS::~WALLS() {
    delete[] walls;
}

int main() {
    ifstream I("input.txt");
    ofstream O("output.txt");
    int p, x, y, z, i;
    I >> p;
    CONTAINER con(0, 200 + 1e-13, 0, 200 + 1e-13, 0, 200 + 1e-13, 10, 10, 10, 8);
    for (i = 0; i < p; i++) {
        I >> x >> y >> z;
        con.put(i, x, y, z);
    }
    auto vols = con.cell_volumes(p);
    for (long double vol: vols) O << fixed << setprecision(2) << vol << endl;
}