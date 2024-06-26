import graphviz

import collections as cs

def create_graph(arr):
    dot = graphviz.Digraph('tree1')
    N = len(arr)
    i = 1

    Q = cs.deque([0])
    dot.node("node0", "{}".format(arr[0]), {"shape": "circle"})
    curPos = 1
    while Q:
        nodeParent = Q.popleft()
        parentI = "node{}".format(nodeParent)

        if N <= curPos:
            continue

        leftI = arr[curPos]
        if leftI is not None:
            Q.append(curPos)
            nameL = "node{}".format(curPos)
            dot.node(nameL, "{}".format(leftI), {"shape": "circle"})
            dot.edge(parentI, nameL)

        curPos += 1
        if N <= curPos:
            continue

        rightI = arr[curPos]
        if rightI is not None:
            Q.append(curPos)
            nameR = "node{}".format(curPos)
            dot.node(nameR, "{}".format(rightI), {"shape": "circle"})
            dot.edge(parentI, nameR)

        curPos += 1


    return dot



    

arr2 = [5,4,7,3,None,2,None,-1,None,9]
arr = [88265,83067,88942,1931,86070,88632,97916,10,40355,83240,87828,88314,88935,93107,98624,None,445,19602,50100,83231,85900,87243,88165,None,88574,88726,None,89038,95508,98191,99899,310,1273,3621,27988,45914,65855,83127,None,84043,85995,86540,None,None,None,None,None,None,None,88962,91698,95310,95878,98106,98287,98910,None,200,None,1030,1731,2125,4675,27601,31475,43587,49227,55475,70179,None,None,83740,84534,None,None,86196,86796,None,None,89588,91950,94022,None,95751,95893,None,None,None,None,None,98928,None,None,None,1167,1631,1874,2004,2836,4649,17674,19836,None,28897,33618,40903,45489,46813,49677,54413,57975,68558,76860,83546,83905,84430,85306,None,None,None,None,89120,91446,91780,92014,93798,95100,None,None,None,96306,None,99471,None,None,None,None,None,None,None,None,2435,3500,4322,None,5519,19447,19795,24476,28854,30868,31856,38458,40672,42266,44336,None,46167,48818,49228,None,50931,54818,57075,62815,67703,69443,73510,80225,None,83672,None,84017,None,None,85101,85665,89040,89207,90061,91565,None,91925,91991,92484,93639,None,94176,None,None,96865,99333,None,None,None,2987,None,4135,4407,5065,16993,19183,19507,None,None,20737,25949,28298,None,29504,31419,31734,32891,34069,39672,None,40822,42183,43332,44030,45044,None,None,47082,None,None,49631,50439,52667,54768,54975,55787,57157,62661,65359,66013,68271,68827,70019,71891,75218,79639,80319,None,None,None,None,84794,85300,None,None,None,89044,None,89260,None,90548,91449,91662,None,None,None,None,92450,92931,93371,None,94127,None,None,97907,99301,None,2864,None,None,None,None,None,4958,5101,15176,17069,18148,19184,19452,19585,20109,21835,24824,27163,28207,28476,29242,30615,31381,None,None,None,32859,None,34036,36073,38586,None,None,None,41442,None,42510,None,43945,44182,44594,None,46997,47305,49550,None,None,50859,51618,53204,54721,None,None,55449,None,56522,None,None,61661,62795,63069,None,None,66664,68027,68393,68757,69151,None,None,71335,72939,74595,76409,79365,79972,80318,81713,None,85058,None,None,None,89061,None,89297,90249,None,None,None,None,None,92443,None,92586,None,None,None,94125,None,97200,None,99023,None,None,None,4770,None,None,5401,8016,15354,None,17488,None,None,None,None,None,None,None,None,None,20404,20982,23635,24642,25159,26662,27243,None,None,None,28676,28945,None,None,None,None,None,None,None,33671,None,35340,37967,None,39461,41251,41715,None,43060,43701,None,None,44239,None,44868,46992,None,None,47402,None,None,None,None,51286,51747,52726,53728,None,None,None,None,55885,None,60390,62129,None,None,None,64826,66192,None,67896,None,68319,None,None,None,68920,69252,70858,71346,71902,73479,73585,74681,75219,76663,78662,79474,79739,None,None,None,81406,82981,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,5330,5506,5545,13304,15211,15364,17108,None,20243,20435,None,21228,22207,23885,None,24710,24964,25506,26020,27015,None,None,None,None,None,28975,33619,33978,34199,35570,37950,38055,39221,39639,None,None,41556,None,42723,None,None,43831,None,None,None,None,46841,None,None,48278,50941,51288,None,52161,None,52845,None,54319,55854,55907,59194,61633,61817,62460,63205,64934,None,None,None,None,None,None,None,None,None,69400,70508,71148,None,71617,None,None,73185,None,None,73989,None,None,None,75982,76475,76708,78223,78928,None,79618,None,79924,81344,None,82149,None,5167,None,None,None,None,5929,8630,13715,15206,None,None,15585,17105,17347,None,None,None,20669,21062,21831,None,22914,None,24245,None,None,24954,None,25207,None,25958,26130,26967,None,None,None,None,None,None,None,34097,None,35526,36008,36698,None,37988,38147,None,39381,39572,None,None,None,None,None,None,43920,None,None,48090,48670,None,51277,None,None,51996,None,None,None,54318,54359,None,None,None,None,58506,59373,61228,None,None,None,62339,None,63155,64814,None,65240,None,None,None,None,None,None,None,None,None,None,73913,74380,75492,None,None,None,None,None,77369,78462,None,78983,None,None,None,None,81336,None,None,82595,5162,5326,None,7609,8152,12283,None,15120,None,None,None,16296,None,None,None,None,None,None,None,None,21478,None,22346,23369,24101,None,None,None,None,None,None,None,None,26476,None,None,34087,None,None,None,None,None,36492,37733,None,None,None,None,None,None,None,None,None,None,None,48130,48515,48767,None,None,None,None,None,None,None,None,58374,59057,None,60085,61197,None,None,None,None,None,64045,None,65155,65332,None,None,None,74469,75452,None,76956,78151,None,None,None,79165,None,None,82266,None,None,None,None,None,6132,8001,None,8374,9289,12817,15088,None,15586,16312,None,21716,None,None,None,23539,None,None,26436,None,None,None,36128,None,36816,None,None,None,None,None,None,None,None,None,58798,None,60025,60119,None,None,63760,64574,None,None,None,None,None,None,None,None,76950,77307,77933,78183,None,None,None,None,5990,6326,None,8007,8370,None,9176,11394,None,13187,15075,None,None,15689,None,None,None,None,None,None,None,None,None,None,None,None,58792,None,None,None,None,None,None,63951,None,None,None,None,None,None,None,None,None,None,None,None,None,6535,None,None,None,None,9056,None,10519,11998,13029,13228,15060,None,None,16240,58738,None,63867,None,None,None,8698,None,9434,11098,11774,None,12856,13131,None,None,14242,None,None,None,None,None,None,None,None,None,None,10365,10941,None,None,11882,None,None,None,None,13730,None,9699,None,10663,11095,None,None,None,None,None,10009,10581,10797,10966]

G = create_graph(arr)
G.render(format="svg")
