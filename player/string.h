#ifndef STRING_H
#define STRING_H
class String
{   struct Letter
    {   char at;
        Letter* xs;
    };

    Letter* headP;
    Letter* tailP;
    Letter* i;

    String(Letter* a, Letter* b, Letter* c)
        {headP = a; i = b; tailP = c;}
    void copy(const char &a, String &b)
    {   if(b.headP != nullptr)
        {   b.clear();
            b.append(a);
        }
        else
            {b.append(a);}
    }
    void copy(Letter* a, String &b)
    {   if(headP != nullptr)
        {   Letter* x = b.headP;
            Letter* y = a;
            Letter* xs = nullptr;
            while(x != nullptr)
            {   if(y->xs == nullptr)
                {   b.tailP = x;
                    xs = x->xs;
                    x->xs = nullptr;
                    x = xs;
                    while(x != nullptr)
                    {   xs = x->xs;
                        delete x;
                        x = xs;
                    }
                    y = y->xs;
                    break;
                }
                else
                {   x->at = y->at;
                    xs = x->xs;
                    y = y->xs;
                    x = xs;
                }
            }
            while(y != nullptr)
                {b.append(y->at); y = y->xs;}
            b.i = b.headP;
        }
        else
            {b.append(a);}
    }
    bool predicate(const char* cmp, const char &left, const char &right) const
    {   if(cmp[0] == '=' && cmp[1] == '=' && cmp[2] == '\0')
            {return left == right;}
        else if(cmp[0] == '!' && cmp[1] == '=' && cmp[2] == '\0')
            {return left != right;}
        else if(cmp[0] == '<' && cmp[2] == '\0')
            {return left < right;}
        else if(cmp[0] == '>' && cmp[2] == '\0')
            {return left > right;}
        else if(cmp[0] == '<' && cmp[1] == '=' && cmp[2] == '\0')
            {return left <= right;}
        else if(cmp[0] == '>' && cmp[1] == '=' && cmp[2] == '\0')
            {return left >= right;}
        else
            {return false;}
    }
    void popFrom(const int &a)
    {   Letter* x = headP;
        Letter* xs = nullptr;
        int n = 0;
        if(headP == tailP)
            {delete headP; headP = nullptr; tailP = nullptr; i = nullptr; return;}
        while(n < (a-1))
        {   if(x == nullptr)
                {return;}
            else
                {x = x->xs; n++;}
        }
        if(x != nullptr)
        {   tailP = x;
            xs = x->xs;
            x->xs = nullptr;
            x = xs;
        }
        while(x != nullptr)
        {   xs = x->xs;
            delete x;
            x = xs;
        }
    }


// ======== PRIVATE CSTRING FUNCTIONS ========
void copy(const char* a, String &b)
{   if(headP != nullptr)
    {   Letter* x = b.headP;
        int n = 0;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   if(a[n] == '\0')
            {   b.tailP = x;
                xs = x->xs;
                x->xs = nullptr;
                x = xs;
                while(x != nullptr)
                {   xs = x->xs;
                    delete x;
                    x = xs;
                }
                n++;
                break;
            }
            else
            {   x->at = a[n];
                xs = x->xs;
                n++;
                x = xs;
            }
        }
        while(a[n] != '\0')
            {b.append(a[n]); n++;}
        b.i = b.headP;
    }
    else
        {b.append(a);}
}


public:
// ======== CONSTRUCTORS ========
    String()
        {headP = nullptr; tailP = nullptr; i = nullptr;}
    String(const char &a)
        {headP = nullptr; tailP = nullptr; i = nullptr; append(a);}
    String(const String &a)
        {headP = nullptr; tailP = nullptr; i = nullptr; append(a);}
    ~String()
        {clear();}
    void operator=(const char &a)
        {copy(a, *this);}
    //void copy(String &a)
    //    {copy(headP, a);}
    void operator=(const String &a)
        {copy(a.i, *this);}


// ======== ACCESSORS ========
    bool null() const
        {return i == nullptr;}
    bool top() const
        {return i == headP;}
    bool sub() const
        {return i != headP;}
    bool single() const
        {return i == tailP;}
    char head() const
        {if(i != nullptr) {return i->at;} else {return '\0';}}
    char front() const
        {return head();}
    char tail() const
        {if(tailP != nullptr) {return tailP->at;} else {return '\0';}}
    char back() const
        {return tail();}
    char operator[](const int &a) const
    {   int n = 0;
        Letter* x = headP;
        while(n < a)
        {   if(x == nullptr)
                {return '\0';}
            else
                {x = x->xs; n++;}
        }
        return x->at;
    }
    int size() const
    {   int n = 0;
        Letter* x = headP;
        while(x != nullptr)
            {x = x->xs; n++;}
        return n;
    }
    int length() const
        {return size();}
    String body() const
    {   if(i != nullptr)
        {   if(i->xs != nullptr)
                {return String(headP, i->xs, tailP);}
        }
        return String();
    }
    String rest() const
        {return body();}
    String operator++() const
        {return body();}


// ======== MUTATORS ========
    void clear()
    {   if(top())
        {   Letter* x;
            while(headP != nullptr)
            {   x = headP;
                headP = headP->xs;
                delete x;
            }
            i = nullptr;
            tailP = nullptr;
        }
        else
        {   headP = nullptr;
            i = nullptr;
            tailP = nullptr;
        }
    }
    void cons(const char &a)
    {   if(top())
        {   Letter* n = new Letter;
            n->at = a;
            n->xs = nullptr;
            if(headP != nullptr)
                {n->xs = headP; headP = n;}
            else
                {headP = n; tailP = n;}
            i = headP;
        }
    }
    void append(const char &a)
    {   if(top())
        {   Letter* n = new Letter;
            n->at = a;
            n->xs = nullptr;
            if(tailP != nullptr)
                {tailP->xs = n; tailP = n;}
            else
                {headP = n; tailP = n; i = headP;}
        }
    }
    void operator+=(const char &a)
        {append(a);}
    void append(Letter* a)
    {   if(top())
        {   Letter* x = a;
            Letter* xs = nullptr;
            while(x != nullptr)
            {   append(x->at);
                xs = x->xs;
                x = xs;
            }
        }
    }
    void append(const String &a)
        {append(a.headP);}
    void operator+=(const String &a)
        {append(a);}
    void chop()
    {   if(top())
        {   Letter* xs = nullptr;
            if(headP != nullptr)
            {   if(headP == tailP)
                    {delete headP; headP = nullptr; tailP = nullptr; i = nullptr;}
                else
                    {xs = headP->xs; delete headP; headP = xs; i = headP;}
            }
        }
    }
    void pop()
    {   if(top())
        {   Letter* x = headP;
            Letter* xs = nullptr;
            if(headP == tailP)
                {delete headP; headP = nullptr; tailP = nullptr; i = nullptr;}
            while(x != nullptr)
            {   xs = x->xs;
                if(xs == tailP)
                    {delete xs; tailP = x; return;}
                else
                    {x = xs;}
            }
        }
    }
    bool removeAt(const int &a)
    {   if(top())
        {   Letter* x = headP;
            Letter* xs = nullptr;
            int n = 1;
            if(a < 1)
                {chop(); return true;}
            if(x != nullptr)
                {xs = x->xs;}
            while(xs != nullptr)
            {   xs = x->xs;
                if(n == a)
                {   if(xs == tailP)
                        {tailP = x;}
                    x->xs = xs->xs;
                    delete xs;
                    return true;
                }
                else
                    {x = xs; n++;}
            }
            return false;
        }
        return false;
    }
    bool remove(const char &a)
    {   if(top())
        {   Letter* x = headP;
            Letter* xs = nullptr;
            if(x != nullptr)
            {   xs = x->xs;
                if(x->at == a)
                    {chop(); return true;}
            }
            while(xs != nullptr)
            {   xs = x->xs;
                if(xs->at == a)
                {   if(xs == tailP)
                        {tailP = x;}
                    x->xs = xs->xs; delete xs;
                    return true;
                }
                else
                    {x = xs;}
            }
            return false;
        }
        return false;
    }
    void swap(String &a)
    {   if(top() && a.top())
        {   Letter* x = headP;
            Letter* y = tailP;
            headP = a.headP; tailP = a.tailP; i = headP;
            a.headP = x; a.tailP = y; a.i = a.headP;
        }
    }


// ======== FUNCTIONS ========
    String drop(const int &a, String &b)
    {   int n = 0;
        if(&b == this)
        {   if(top())
            {   while(n < a)
                    {chop(); n++;}
            }
            /*else
            {   Letter* x = i;
                i = headP;
                while(headP != x)
                    {chop();}
                while(n < a)
                    {chop(); n++;}
            }*/
            return *this;
        }
        else
        {   Letter* x = i;
            while(n < a)
            {   if(x == nullptr)
                    {b.clear(); return b;}
                x = x->xs; n++;
            }
            copy(x,b);
            return b;
        }
    }
    String take(const int &a, String &b)
    {   if(&b == this)
        {   if(top())
                {popFrom(a);}
            /*else
            {   Letter* x = i;
                i = headP;
                while(headP != x)
                    {chop();}
                popFrom(a);
            }*/
            return *this;
        }
        else
        {   Letter* x = i;
            Letter* y = b.headP;
            int n = 0;
            while(n < a && x != nullptr)
            {   if(y != nullptr)
                {   y->at = x->at;
                    x = x->xs; y = y->xs;
                    n++;
                }
                else
                {   b.append(x->at);
                    x = x->xs;
                    n++;
                }
            }
            b.popFrom(n);
            return b;
        }
    }
    String filter(const char* a, const char &b, String &c)
    {   if(&c == this)
        {   if(top())
            {   Letter* x = headP;
                Letter* xs = nullptr;
                if(x != nullptr)
                {   if(predicate(a, x->at, b))
                        {chop(); x = headP;}
                }
                while(x != nullptr)
                {   xs = x->xs;
                    if(xs != nullptr)
                    {   if(predicate(a, xs->at, b))
                        {   if(xs == tailP)
                                {tailP = x;}
                            x->xs = xs->xs; delete xs;
                        }
                    }
                    x = x->xs;
                }
            }
            return *this;
        }
        else
        {   Letter* x = i;
            Letter* y = c.headP;
            int n = 0;
            while(x != nullptr)
            {   if(!predicate(a, x->at, b))
                {   if(y != nullptr)
                        {y->at = x->at; y = y->xs; n++;}
                    else
                        {c.append(x->at); n++;}
                }
                x = x->xs;
            }
            c.popFrom(n);
            return c;
        }
    }
    String filter(const char* a, const String &b, String &c)
    {   if(&c == this)
        {   if(top())
            {   Letter* x = headP;
                Letter* y = b.i;
                Letter* xs = nullptr;
                bool cnd = false;
                if(x != nullptr)
                {   while(y != nullptr)
                    {   if(predicate(a, x->at, y->at))
                            {cnd = true; break;}
                        y = y->xs;
                    }
                    if(cnd)
                        {chop(); x = headP; cnd = false;}
                    y = b.i;
                }
                while(x != nullptr)
                {   xs = x->xs;
                    if(xs != nullptr)
                    {   while(y != nullptr)
                        {   if(predicate(a, xs->at, y->at))
                                {cnd = true; break;}
                            y = y->xs;
                        }
                        if(cnd)
                        {   if(xs == tailP)
                                {tailP = x;}
                            x->xs = xs->xs; delete xs;
                            cnd = false;
                        }
                        else
                            {x = x->xs;}
                        y = b.i;
                    }
                    x = x->xs;
                }
            }
            return *this;
        }
        else
        {   Letter* x = i;
            Letter* y = c.headP;
            Letter* z = b.i;
            int n = 0;
            bool cnd = false;
            while(x != nullptr)
            {   while(z != nullptr)
                {   if(predicate(a, x->at, z->at))
                        {cnd = true; break;}
                    z = z->xs;
                }
                if(!cnd)
                {   if(y != nullptr)
                        {y->at = x->at; y = y->xs; n++;}
                    else
                        {c.append(x->at); n++;}
                }
                x = x->xs;
                z = b.i;
                cnd = false;
            }
            c.popFrom(n);
            return c;
        }
    }
    String operator-(const String& a)
        {return filter("==", a, *this);}
    String nub(String &a)
    {   if(&a == this)
        {   if(top())
            {   Letter* x = headP;
                Letter* y = nullptr;
                Letter* ys = nullptr;
                while(x != nullptr)
                {   y = x;
                    while(y != nullptr)
                    {   ys = y->xs;
                        if(ys != nullptr)
                        {   if(ys->at == x->at)
                            {   if(ys == tailP)
                                    {tailP = y;}
                                y->xs = ys->xs; delete ys;
                            }
                        }
                        y = y->xs;
                    }
                    x = x->xs;
                }
                return *this;
            }
            else
                {return String();}
        }
        else
        {
            return a;
        }
    }

// ======== COMPARISONS =========
    bool elem(const char &a) const
    {   Letter* x = i;
        while(x != nullptr)
        {   if(x->at == a)
                {return true;}
            else
                {x = x->xs;}
        }
        return false;
    }
    bool notElem(const char &a) const
        {return !elem(a);}
    bool elem(const String &a) const
    {   Letter* x = i;
        Letter* xs = nullptr;
        Letter* y = a.i;
        while(x != nullptr)
        {   if(y != nullptr)
            {   if(x->at == y->at)
                {   xs = x;
                    y = a.i;
                    while(y != nullptr)
                    {   if(xs == nullptr)
                            {return false;}
                        else if(xs->at != y->at)
                            {break;}
                        y = y->xs; xs = xs->xs;
                    }
                    if(y == nullptr)
                        {return true;}
                }
            }
            x = x->xs;
        }
        return false;
    }
    bool operator==(const String &a) const
    {   Letter* x = i;
        Letter* y = a.i;
        while(x != nullptr)
        {   if(y == nullptr)
                {return false;}
            else if(x->at != y->at)
                {return false;}
            else
                {x = x->xs; y = y->xs;}
        }
        if(y == nullptr)
            {return true;}
        else
            {return false;}
    }
    bool operator !=(const String &a) const
        {return !(*this == a);}
    bool operator<(const String &a) const
    {   Letter* x = i;
        Letter* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at > y->at)
                {return false;}
            else if(x->at == y->at && y->xs == nullptr)
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator>(const String &a) const
    {   Letter* x = i;
        Letter* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at < y->at)
                {return false;}
            else if(x->at == y->at && x->xs == nullptr)
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator<=(const String &a) const
    {   Letter* x = i;
        Letter* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at > y->at)
                {return false;}
            else if(x->at == y->at && (x->xs != nullptr && y->xs == nullptr))
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator>=(const String &a) const
    {   Letter* x = i;
        Letter* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at < y->at)
                {return false;}
            else if(x->at == y->at && (x->xs == nullptr && y->xs != nullptr))
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }


// ======== SPECIAL STRING FUNCTIONS ========
    String lower(String &a)
    {   if(&a == this)
        {   if(top())
            {   Letter* x = headP;
                while(x != nullptr)
                {   if(x->at < 91 && x->at > 64)
                        {x->at = (x->at + 32);}
                    x = x->xs;
                }
                return *this;
            }
            return String();
        }
        else
        {
            return a;
        }
    }
    String upper(String &a)
    {   if(&a == this)
        {   if(top())
            {   Letter* x = headP;
                while(x != nullptr)
                {   if(x->at < 123 && x->at > 96)
                        {x->at = (x->at - 32);}
                    x = x->xs;
                }
                return *this;
            }
            return String();
        }
        else
        {
            return a;
        }
    }
    String word(String &a, String &b)
    {   if(b.top())
        {   Letter* x = a.i;
            Letter* y = b.headP;
            int n = 0;
            while(x != nullptr)
            {   if(x->at == ' ')
                    {break;}
                if(y != nullptr)
                {   y->at = x->at;
                    y = y->xs;
                }
                else
                    {b.append(x->at);}
                x = x->xs;
                n++;
            }
            b.popFrom(n);
        }
        if(a.top())
        {   Letter* x = a.headP;
            while(x != nullptr)
            {   if(x->at == ' ')
                {   x = x->xs;
                    while(x != nullptr)
                    {   if(x->at == ' ')
                            {x = x->xs; a.chop();}
                        else
                            {break;}
                    }
                    break;
                }
                x = x->xs;
                a.chop();
            }
            a.chop();
        }
        return b;
    }



// ======== CSTRING FUNCTIONS ========
    char* cStr() const
    {   if(i != nullptr)
        {   int s = size();
            char* ret = new  char[s];
            Letter* x = i;
            int n = 0;
            while(x != nullptr)
            {   ret[n] = x->at;
                x = x->xs;
                n++;
            }
            ret[s] = '\0';
            return ret;
        }
        else
        {   char* ret = new char[0];
            return ret;
        }
    }
    String(const char* a)
        {headP = nullptr; tailP = nullptr; i = nullptr; append(a);}
    void operator=(const char* a)
        {copy(a, *this);}
    void append(const char* a)
    {   int n = 0;
        while(a[n] != '\0')
        {   append(a[n]);
            n++;
        }
    }
    void operator+=(const char* a)
        {append(a);}
    String filter(const char* a, const char* b, String &c)
        {return filter(a, String(b), c);}
    String operator-(const char* a)
        {return filter("==", String(a), *this);}
    bool elem(const char* a)
        {return elem(String(a));} //temporary workaround

};
#endif