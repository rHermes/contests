import subprocess as ps
import math


BIN_PLACE = "/home/rhermes/commons/projects/contests/plz-out/bin/dmoj/cco06p3"
# BIN_PLACE = "/home/rhermes/commons/projects/contests/dmoj/yac8/p5"

def make_sure_its_up_to_date():
    WL = "/home/rhermes/commons/projects/contests/pleasew"

    pl = ps.run([WL, "build", "//dmoj:cco06p3"], capture_output=True)
    pl.check_returncode()

# OK so we are going to create some tests here, but 
def to_problem_format(text):
    return "1\n" + text

def get_bitstring(text):
    inp = "1\n" + text

    gv  = ps.run(BIN_PLACE,
                 input=inp.encode("utf-8"),
                 capture_output=True,
                 )
    gv.check_returncode()
    return gv.stdout.decode('utf-8')


def parse_bitstring(bitstring):
    inp = "2\n" + bitstring

    gv = ps.run(BIN_PLACE,
                input=inp.encode("utf-8"),
                capture_output=True,
                )
    gv.check_returncode()

    return gv.stdout.decode('utf-8')


def perform_test(text):
    bs = get_bitstring(text)
    parsed = parse_bitstring(bs)
    assert(text == parsed)

    return len(bs)

def eval_file(fp):

    text = ""
    with open(fp, encoding="ascii", errors="replace") as f:
        text = f.read()

    # we just clean up the input now
    lp = list(text)
    for i,c in enumerate(lp):
        if not (ord(c) == 10 or 32 <= ord(c) <= 126):
            lp[i] = '?'

    
    text = "".join(lp)
    bsLen = perform_test(text)

    # if we included the frequency table in the beginning of the input.
    # bsLen += 8*4*96*96
    rat = bsLen/len(text)
    if 8 < rat:
        score = 0
    else:
        score = min(100, 50 * math.sqrt(8 - rat))

    # print("Evauluating {}: Bitstring was {} long, having a ratio of {}, meaning we got a score of {}".format(
    #     fp, bsLen, rat, score,))
    print("Evauluating {:10}: ratio of {:.4f}, score of {:6.2f}".format(fp, rat, score,))

if __name__ == "__main__":
    make_sure_its_up_to_date()

    import sys
    files = sys.argv[1:]
    try:
        import natsort
        # files = natsort.natsorted(files)
        files = natsort.os_sorted(files)
    except:
        pass

    for file in files:
        eval_file(file)
