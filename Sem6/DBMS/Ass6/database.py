import re, json, pandas as pd
class DataDict:
    def __init__(self):
        self.meta_data = json.load(open('meta_data.json', 'r'))

    def valid_table(self, table_name):
        if table_name in self.meta_data["TABLES"]:
            return True
        else:
            return False

    def valid_attribute(self, table_name, attribute_name):
        if table_name in self.meta_data["TABLES"]:
            attributes = [item["attribute_name"] for item in self.meta_data["TABLES"]["attributes"]]
            if attribute_name in attributes:
                return True
            else:
                return False

    def get_all_attributes(self, table_name):
        if table_name in self.meta_data["TABLES"]:
            return  [item["attribute_name"] for item in self.meta_data["TABLES"][table_name]["attributes"]]

    def get_table_path(self, table_name):
        if table_name in self.meta_data["TABLES"]:
            return self.meta_data["TABLES"][table_name]["file_path"]

class QueryProcessor:
    def __init__(self):
        self.data_dict = DataDict()

    def query_parser(self, query):
        try:
            tokens = re.split(', | ', query)
            if tokens[0].upper() == 'SELECT'.upper():
                from_index = tokens.index("FROM")
                attributes = tokens[1:from_index]
                table_name = tokens[from_index+1]
                if '*' in attributes:
                    attributes = self.data_dict.get_all_attributes(table_name)
                table_path = self.data_dict.get_table_path(table_name)
                print(self.retrive_data(table_path, attributes))
            else:
                return None
        except Exception as e:
            print(e)

    def retrive_data(self, table_path, attributes):
        dataframe = pd.read_csv(table_path)
        return dataframe[attributes]

if __name__ == '__main__':
    Q = QueryProcessor()
    Q.query_parser(input())
