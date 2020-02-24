import json


# 从文件中加载数据
def load_data():
    with open('stations.json', 'r', encoding='utf-8') as f:
        stations = json.load(f)
    with open('routes.json', 'r', encoding='utf-8') as f:
        routes = json.load(f)
    with open('edges.json', 'r', encoding='utf-8') as f:
        edges = json.load(f)
    return stations, routes, edges


# 相邻两站点之间的距离
def get_edge_length(sta1, sta2):
    name = "{}_{}".format(sta1, sta2)
    name_ = "{}_{}".format(sta2, sta1)
    if not edges.get(name) == None:
        return edges.get(name)  # python3.8优化
    elif not edges.get(name_) == None:
        return edges.get(name_)
    else:
        print("Wrong")  # 最短路径问题


# 获取某条可行路线的距离
def get_distance(routes_list):
    length = 0
    for i in range(len(routes_list) - 1):
        length += get_edge_length(routes_list[i], routes_list[i + 1])
    return length


# 两站是否有公交车直达
def thru(sta1, sta2):
    for route in routes.keys():
        if sta1 in routes[route] and sta2 in routes[route]:
            return True
    else:
        return False


# 已知两站直达，返回直达路线的信息
def get_thru_routes(sta1, sta2):
    routes_ = [route for route in routes.keys() if sta1 in routes[route]
               and sta2 in routes[route] and routes[route].index(sta1) < routes[route].index(sta2)]
    the_thru_route = []
    if not len(routes_) == 0:
        for route in routes_:
            route_temp = routes[route]
            start = route_temp.index(sta1)
            end = route_temp.index(sta2)
            stations_list = route_temp[start:end+1]
            the_thru_route.append(
                ((route, '--({})--'.format(route).join(stations_list), get_distance(stations_list))))
            # (直达路线，路线及包含的具体站点， 距离)
    return the_thru_route


# 两站不能直达，返回可能需要换乘的路线
def get_routes(sta1, sta2):
    route1 = stations[sta1]  # 经过sta1的所有路线
    route2 = stations[sta2]  # 经过sta2的所有路线
    solutions = []  # 需要中转的方案
    routes_ = []
    for route in route1:
        for route_ in route2:
            start = routes[route].index(sta1)
            end = routes[route_].index(sta2)
            if not len(set(routes[route][start+1:]) & set(routes[route_][:end])) == 0:
                solutions.append([route, route_, list(
                    set(routes[route]) & set(routes[route_]))])
                # [线路1，线路2，[中转站]]
    if not len(solutions) == 0:
        for solution in solutions:
            transit_station = routes[solution[0]].index(
                solution[2][0])  # (第1个)中转站在路线1中的位置
            transit_station_ = routes[solution[1]].index(
                solution[2][0])  # (第1个)中转站在路线2中的位置
            start = routes[solution[0]].index(sta1)
            end = routes[solution[1]].index(sta2)

            stations_list = routes[solution[0]][start:transit_station] + \
                routes[solution[1]][transit_station_:end+1]

            half_1 = '--({})--'.format(solution[0]).join(
                routes[solution[0]][start:transit_station+1])
            half_2 = '--({})--'.format(solution[1]).join(
                routes[solution[1]][transit_station_+1:end+1])
            stations_str = half_1+'(换乘)--({})--'.format(solution[1])+half_2

            routes_.append(('{%s}转{%s}' %
                            (solution[0], solution[1]), stations_str, get_distance(stations_list)))
        return routes_
    else:
        return []


# 如果有多条线路则返回最短路线
def shortest_route(routes):
    if len(routes) == 0:
        return "Can't arrive!!!"
    else:
        shortest = routes[0]
        for route in routes:
            if route[2] < shortest[2]:
                shortest = route
        return shortest


# 根据站点返回公交路路线
def take_bus(sta1, sta2):
    if sta1 in stations.keys() and sta2 in stations.keys():
        if thru(sta1, sta2):
            print(shortest_route(get_thru_routes(sta1, sta2)))
        else:
            print(shortest_route(get_routes(sta1, sta2)))
    else:
        print("Input Wrong!!!")


# 更新数据到文件中
def refresh_data(stations, routes, edges):
    with open('stations.json', 'w', encoding='utf-8') as f:
        json.dump(stations, f, ensure_ascii=False)
    with open('routes.json', 'w', encoding='utf-8') as f:
        json.dump(routes, f, ensure_ascii=False)
    with open('edges.json', 'w', encoding='utf-8') as f:
        json.dump(edges, f, ensure_ascii=False)


# 路线信息
def route_info(route):
    if route in routes.keys():
        print(route + ': ' + '-->--'.join(routes[route]))
    else:
        print("Route {} doesn't exist!!!".format(route))


# 站点信息
def station_info(station):
    if station in stations.keys():
        print('routes: ' + ', '.join(stations[station]))
    else:
        print("Station {} doesn't exist!!!".format(station))


# 检查数据
def check(sta, stations_list, distance_list, code):
    if code == 0:
        if sta in stations.keys():
            return False
    elif code == 1:
        if sta not in stations.keys():
            return False
    if len(stations_list) != len(distance_list):
        return False
    for station in stations_list:
        if station not in stations.keys():
            return False
    return True


# 添加站点_
def add_station(sta, stations_list, distance_list):
    # 检查数据
    if check(sta, stations_list, distance_list, 0):
        stations[sta] = []
        for i in range(len(stations_list)):
            # name = '{}_{}'.format(sta, stations_list[i])
            # name_ = '{}_{}'.format(stations_list[i], sta)
            # edges[name] = distance_list[i]
            # edges[name_] = distance_list[i]
            add_edge(sta, stations_list[i], distance_list[i])


# 修改站点
def change_station(sta, stations_list, distance_list):
    # 检查数据
    if check(sta, stations_list, distance_list, 1):
        for i in range(len(stations_list)):
            add_edge(sta, stations_list[i], distance_list[i])


# 删除站点
def del_station(station):
    if station in stations.keys():
        for route in routes.keys():
            if station in routes[route]:
                routes[route].remove(station)
        for sta in stations.keys():
            temp = '{}_{}'.format(sta, station)
            temp_ = '{}_{}'.format(station, sta)
            if temp in edges.keys():
                del edges[temp]
            if temp_ in edges.keys():
                del edges[temp_]
        del stations[station]
    else:
        print("Station {} doesn't exist!!!".format(station))


# 增加edge
def add_edge(sta1, sta2, distance):
    if sta1 in stations.keys() and sta2 in stations.keys():
        name = '{}_{}'.format(sta1, sta2)
        name_ = '{}_{}'.format(sta2, sta1)
        if edges.get(name) != None or edges.get(name_) != None:
            print("Edge {} exist already!!!".format(name))
        else:
            edges[name] = distance
            edges[name_] = distance

    else:
        print("sta1 and sta2 must be exist!!!")


# 修改edge
def change_edge(sta1, sta2, distance):
    if sta1 in stations.keys() and sta2 in stations.keys():
        name = '{}_{}'.format(sta1, sta2)
        name_ = '{}_{}'.format(sta2, sta1)
        edges[name] = distance
        edges[name_] = distance
    else:
        print("sta1 and sta2 must be exist!!!")


# 删除edge
def del_edge(sta1, sta2):
    if sta1 in stations.keys() and sta2 in stations.keys():
        name = '{}_{}'.format(sta1, sta2)
        name_ = '{}_{}'.format(sta2, sta1)
        if edges.get(name) == None and edges.get(name_) == None:
            print("{} is not exist!!!".format(name))
        else:
            if edges.get(name) != None:
                del edges[name]
            if edges.get(name_) != None:
                del edges[name_]
    else:
        print("sta1 and sta2 must be exist!!!")


# 检查statins_list中的station是否都存在，并相邻
def check_stations(stations_list):
    for sta in stations_list:
        if sta not in stations.keys():
            print("Station {} isn't exist!!!".format(sta))
            return False
    for i in range(len(stations_list)-1):
        temp = '{}_{}'.format(stations_list[i], stations_list[i+1])
        temp_ = '{}_{}'.format(stations_list[i+1], stations_list[i])
        if temp not in edges.keys() and temp_ not in edges.keys():
            print("Edge {} isn't exist!!!".format(temp))
            return False
    return True


# 增加公交路线
def add_route(route_num, stations_list):
    name = '{}_U'.format(route_num)
    name_ = '{}_D'.format(route_num)
    if route_num.get(name) == None and route_num.get(name_) == None:
        if check_stations(stations_list):
            for sta in stations_list:
                stations[sta] += [name, name_]
            routes[name] = stations_list
            routes[name_] = stations_list
    else:
        print("Route {} is already exist!!!".format(route_num))


# 修改公交路线
def change_route(route_num, stations_list):
    name = '{}_U'.format(route_num)
    name_ = '{}_D'.format(route_num)
    if routes.get(name) != None and check_stations(stations_list):
        original = routes[name]
        for station in original:
            stations[station].remove(name)  # 删除原有数据
            stations[station].remove(name_)
        for station in stations_list:  # 添加新数据
            stations[station] += [name, name_]
        routes[name] = stations_list  # 添加新数据
        routes[name_] = list(reversed(stations_list))


# 删除公交路线
def del_route(route_num):
    name = '{}_U'.format(route_num)
    name_ = '{}_D'.format(route_num)
    if name in routes.keys():
        if routes.get(name) != None:
            del routes[name]
        if routes.get(name_) != None:
            del routes[name_]
        for station in stations.keys():
            if name in stations[station]:
                stations[station] = stations[station].remove(name)
            if name_ in stations[station]:
                stations[station] = stations[station].remove(name_)
    else:
        print("{} and {} are not exist!!!".format(name, name_))


def run():
    menu = """
    ***************************
    *  Functions:             *
    *  1.Route info           *
    *  2.Station info         *
    *  3.Find route           *
    *  4.Add station          *
    *  5.Change station info  *
    *  6.Delete station       *
    *  7.Add edge             *
    *  8.Change edge info     *
    *  9.Delete edge          *
    *  10.Add route           *
    *  11.Change route info   *
    *  12.Delete route        *
    *  13.Show all info       *
    ***************************
    """
    print(menu)
    num = input("Enter the num of function:")
    if num == '1':
        t = input("Enter the route's name:")
        route_info(t)
    elif num == '2':
        t = input("Enter the station's name:")
        station_info(t)
    elif num == '3':
        t = input("Enter the start and end station(like A,B ):")
        try:
            t_ = t.split(',')
            start, end = t_
            take_bus(start, end)
        except:
            print("Input Error!!!")
    elif num == '4':
        sta = input("Enter the station's name:")
        sta_list = input("Enter the adjacent station list(like A,B,C):")
        dis_list = input("Enter the adjacent distance(like 100,200,300)")
        try:
            sta_list = sta_list.split(',')
            dis_list = [int(i) for i in dis_list.split(',')]
            add_station(sta, sta_list, dis_list)
        except:
            print("Input Error!!!")
    elif num == '5':
        sta = input("Enter the station's name:")
        # check
        sta_list = input("Enter the adjacent station list(like A,B,C):")
        dis_list = input("Enter the adjacent distance(like 100,200,300)")
        try:
            sta_list = sta_list.split(',')
            dis_list = [int(i) for i in dis_list.split(',')]
            change_station(sta, sta_list, dis_list)
        except:
            print("Input Error!!!")
    elif num == '6':
        sta = input("Enter the station's name:")
        del_station(sta)
    elif num == '7':
        t = input("Enter the start end and distance(like A,B,100):")
        try:
            t_ = t.split(',')
            start, end = t_[:2]
            dis = int(t_[2])
            add_edge(start, end, dis)
        except:
            print("Input Error!!!")
    elif num == '8':
        t = input("Enter the start end and distance(like A,B,100):")
        try:
            t_ = t.split(',')
            start, end = t_[:2]
            dis = int(t_[2])
            add_edge(start, end, dis)
        except:
            print("Input Error!!!")
    elif num == '9':
        t = input("Enter the start and end station's name(like A,B):")
        try:
            start, end = t.split(',')
            del_edge(start, end)
        except:
            print("Input Error!!!")
    elif num == '10':
        route_new = input("Enter the new route's num:")
        sta_list = input("Enter the stations of the route(Like A,B,C,D):")
        try:
            route_num = int(route_new)
            sta_list = sta_list.split(',')
            add_route(route_num, sta_list)
        except:
            print("Input Error!!!")
    elif num == '11':
        route_new = input("Enter the new route's num:")
        sta_list = input("Enter the stations of the route(Like A,B,C,D):")
        try:
            route_num = int(route_new)
            sta_list = sta_list.split(',')
            change_route(route_num, sta_list)
        except:
            print("Input Error!!!")
    elif num == '12':
        t = input("Enter the num of the route:(like 1)")
        try:
            del_route(int(t))
        except:
            print("Input Error!!!")
    elif num == '13':
        # stations_ = json.dumps(stations, indent=2, sort_keys=True)
        # edges_ = json.dumps(edges, indent=2, sort_keys=True)
        # routes_ = json.dumps(routes, indent=2, sort_keys=True)
        print(stations)
        print(edges)
        print(routes)
    else:
        print("Input Error!!!")

    con = input("Continue? Y or N:")
    if con != "N" and con != "n":
        run()


if __name__ == '__main__':
    stations, routes, edges = load_data()
    run()
    flag = input("Save the data?(Y or N)")
    if flag != 'N' and flag != 'n':
        refresh_data(stations, routes, edges)
#     change_route(1,["A","B","C","D","E"])
#     take_bus("A","E")
#     # take_bus("A", "E")
#     # route_info("1_U")
#     # station_info("X")
#     # add_station_("X", ["A","B"], [100,100])
#     # change_route(1,["A","X","B","C","H"])
#     # route_info("1_U")
#     # take_bus("A", "H")
#     # change_route(1,["A","B","C","H"])
#     # route_info("1_U")
#     # take_bus("A","H")
#     print(stations)
#     print(edges)
#     print(routes)
#     # refresh_data(stations, routes, edges)
