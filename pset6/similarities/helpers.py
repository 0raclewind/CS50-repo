from nltk.tokenize import sent_tokenize

def compare(a, b):
    """Compare two lists and return final list without duplicates"""
    final = list(set(a) & set(b))
    return final

def substringify(a, n):
    """Takes input as a string and returns list of items of lenght n"""
    final = []
    for index in range(len(a) - n + 1):
        final.append(a[index:index+n])
    return final

def lines(a, b):
    """Return lines in both a and b"""
    split1 = a.split('\n')
    split2 = b.split('\n')

    return compare(split1, split2)

def sentences(a, b):
    """Return sentences in both a and b"""
    sent1 = sent_tokenize(a)
    sent2 = sent_tokenize(b)

    return compare(sent1, sent2)

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substr1 = substringify(a, n)
    substr2 = substringify(b, n)

    return compare(substr1, substr2)
