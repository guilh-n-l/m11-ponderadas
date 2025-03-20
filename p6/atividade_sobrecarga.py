class Fracao:
    @classmethod
    def _mdc_euclides(cls, n, d):
        return n if d == 0 else cls._mdc_euclides(d, n % d)

    mdc_euclides = _mdc_euclides

    @classmethod
    def _reduce(cls, n, d):
        mdc = cls._mdc_euclides(n, d)
        return n // mdc, d // mdc

    def _from_nums(self, n, d):
        self._n = n
        self._d = d
        return self

    def _copy(self, f):
        self._from_nums(f._n, f._d)
        return self

    def invert(self):
        return Fracao(self._d, self._n)

    def reduce(self):
        self._from_nums(*Fracao._reduce(self._n, self._d))

    def __init__(self, n, d):
        if d == 0:
            raise ZeroDivisionError("O denominador não pode ser zero")
        self._from_nums(n, d)
        self.reduce()

    def __str__(self):
        return f"{self['n']}/{self['d']}"

    __repr__ = __str__

    def __float__(self):
        return self._n / self._d

    def __add__(self, f):
        return Fracao(f._d * self._n + self._d * f._n, self._d * f._d)

    def __sub__(self, f):
        return Fracao(f._d * self._n - self._d * f._n, self._d * f._d)

    def __mul__(self, f):
        return Fracao(self._n * f._n, self._d * f._d)

    def __truediv__(self, f):
        return self * f.invert()

    def __iadd__(self, f):
        return self._copy(self + f)

    def __isub__(self, f):
        return self._copy(self - f)

    def __imul__(self, f):
        return self._copy(self * f)

    def __itruediv__(self, f):
        return self._copy(self / f)

    def __lt__(self, f):
        return self._n * f._d < f._n * self._d

    def __gt__(self, f):
        return self._n * f._d > f._n * self._d

    def __eq__(self, f):
        return self._n == f._n and self._d == f._d

    def __le__(self, f):
        return self < f or self == f

    def __ge__(self, f):
        return self > f or self == f

    def __getitem__(self, k):
        CVT = {
            "n": self._n,
            "numerador": self._n,
            "d": self._d,
            "denominador": self._d,
        }
        return CVT.get(k)

    def __setitem__(self, k, v):
        match k:
            case i if i in ["numerador", "n"]:
                self._copy(Fracao(v, self["d"]))
            case i if i in ["denominador", "d"]:
                self._copy(Fracao(self["n"], v))
