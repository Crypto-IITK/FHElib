import torch
import math

def Enc_FHE(params, pk, mu):

    n,q,x,m = params
    l = math.floor(math.log2(q)) + 1
    N = (n+1)*l
    R = torch.Tensor(N,m).uniform_(0,1)
    R = torch.bernoulli(R)
    
    C = lib_name.Flatten( torch.eye(N)*mu + lib_name.BitDecomp(R,pk))

    return C

def Enc_IDFHE(MPK, ID, m):

    A_0 , A_ib, z, d = MPK
    #ask about D_dash and A_ib
    
    m_dash = A_dash.size(1)
    mu_vec = torch.zeros(1,m_dash)
    mu_vec[0,0] = mu*math.floor(q/2)

    r = torch.Tensor(1, n).random_(0, (q-1))
    e = torch.rand(1, m_dash)

    c_id = torch.mv(r, A_dash) + e + mu_vec
    return c_id

def Enc_ABFHE(MPK, ID, m):
    A_01 , A_ib, k, d = MPK
    A_x =               #ask the doubts about them
    A_x_dash = 

    mu_vec = torch.zeros(1, 1 + k*m)
    mu_vec[0,0] = mu*math.floor(q/2)
    
    r = torch.Tensor(1, n).random_(0, (q-1))
    e = torch.rand(1, 1 + k*m)

    c_x = torch.mv(r, A_x_dash) + e + mu_vec
    return x, c_x

