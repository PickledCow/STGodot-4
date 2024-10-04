# It's sooooo bad.....

import xmltodict, json
import sys, os

wiki_root = "https://github.com/PickledCow/STGodot-4/wiki/"
godot_wiki_root = "https://docs.godotengine.org/en/stable/classes/class_"


def get_class_methods_and_members(class_list: list, class_list_index: dict, class_name: str) -> list:
    methods_and_members = {"methods": [], "members": []}


    class_index = class_list_index[class_name]
    o = class_list[class_index]

    parent_name = o["class"]["@inherits"]

    # Add our own methods and members first
    if "methods" in o["class"].keys():
        raw_methods = o["class"]["methods"]["method"]
        
        if type(raw_methods) is list:
            for raw_method in raw_methods:
                method = {}
                method["name"] = raw_method["@name"]
                method["type"] = raw_method["return"]["@type"]
                method["description"] = raw_method["description"]

                params = []
                if "param" in raw_method.keys():
                    raw_params = raw_method["param"]
                    if type(raw_params) is list:
                        for raw_param in raw_method["param"]:
                            param = {}
                            param["name"] = raw_param["@name"]
                            param["type"] = raw_param["@type"]
                            params.append(param)
                    elif type(raw_params) is dict:
                        raw_param = raw_method["param"]
                        param = {}
                        param["name"] = raw_param["@name"]
                        param["type"] = raw_param["@type"]
                        params.append(param)
                method["params"] = params
                methods_and_members["methods"].append(method) 

        elif type(raw_methods) is dict:
            raw_method = raw_methods
            method = {}
            method["name"] = raw_method["@name"]
            method["type"] = raw_method["return"]["@type"]
            method["description"] = raw_method["description"]

            params = []
            if "param" in raw_method.keys():
                raw_params = raw_method["param"]
                if type(raw_params) is list:
                    for raw_param in raw_method["param"]:
                        param = {}
                        param["name"] = raw_param["@name"]
                        param["type"] = raw_param["@type"]
                        params.append(param)
                elif type(raw_params) is dict:
                    raw_param = raw_method["param"]
                    param = {}
                    param["name"] = raw_param["@name"]
                    param["type"] = raw_param["@type"]
                    params.append(param)
            method["params"] = params
        
            methods_and_members["methods"].append(method) 


    if "members" in o["class"].keys():
            raw_members = o["class"]["members"]["member"]
            if type(raw_members) is list:
                for raw_member in raw_members:
                    member = {}
                    member["name"] = raw_member["@name"]
                    member["type"] = raw_member["@type"]
                    member_default = ""
                    if "@default" in raw_member.keys():
                        member_default = raw_member["@default"]
                    member["default"] = member_default
                    member_description = ""
                    if "#text" in raw_member.keys():
                        member_description = raw_member["#text"]
                    member["description"] = member_description
                    methods_and_members["members"].append(member) 

            elif type(raw_members) is dict:
                raw_member = raw_members
                member = {}
                member["name"] = raw_member["@name"]
                member["type"] = raw_member["@type"]
                member_default = ""
                if "@default" in raw_member.keys():
                    member_default = raw_member["@default"]
                member["default"] = member_default
                member_description = ""
                if "#text" in raw_member.keys():
                    member_description = raw_member["#text"]
                member["description"] = member_description
                methods_and_members["members"].append(member)


    # Then add our parent ones
    if parent_name in class_list_index.keys():
        parent_methods_and_members = get_class_methods_and_members(class_list, class_list_index, parent_name)
        methods_and_members["members"] += parent_methods_and_members["members"]
        methods_and_members["methods"] += parent_methods_and_members["methods"]

    return methods_and_members


def get_inheritance(class_list: list, class_list_index: dict, class_name: str, first: bool) -> str:
    # A local version exists
    if class_name in class_list_index:
        class_index = class_list_index[class_name]
        o = class_list[class_index]
        parent_name = o["class"]["@inherits"]
        parent_path = get_inheritance(class_list, class_list_index, parent_name, False)
        
        if first:
            return f'{parent_path}'
            

        return f'[{class_name}]({wiki_root + class_name}) < {parent_path}'


    # We now are pointing at Godot's internal classes
    else:
        return f'[{class_name}]({godot_wiki_root + class_name.lower()}.html)'
    

def get_children(class_list_index: dict, class_name: str) -> str:
    return_text = ", "
    if class_name in class_list_index:
        return_text = return_text[:-2]
        for child_name in children_list[class_name]:
            return_text += f'[{child_name}]({wiki_root + child_name}), '
    
    return return_text
    


if __name__ == "__main__":

    class_list = []
    class_list_index = {}

    children_list = {}

    file_names = []
    
    # Get a list of classes first for inheritance of members and methods
    i = 0
    for file in os.listdir("./doc_classes/"):
        file_names.append(file)
        file_name = "./doc_classes/" + file
        # file_name = "./doc_classes/CollisionBulletKit.xml" # Delete later
        f = open(file_name, "r")
        o = xmltodict.parse(f.read())

        class_list.append(o)
        class_list_index[o["class"]["@name"]] = i
        children_list[o["class"]["@name"]] = []

        i += 1

        f.close()
    
    # Fill list of children
    for o in class_list:
        class_name = o["class"]["@name"]
        parent_name = o["class"]["@inherits"]

        if parent_name in children_list:
            children_list[parent_name].append(class_name)
    
    # Now generate the md files
    
    file_index = 0

    for o in class_list:

        class_name = o["class"]["@name"]
        text = f'### **Inherits:** {get_inheritance(class_list, class_list_index, class_name, True)}\n'

        children_text = get_children(class_list_index, class_name)[:-2]


        text += f'### **Inherited By: {children_text}**\n'

        

        class_brief_description = o["class"]["brief_description"]
        class_description = o["class"]["description"]

        if type(class_brief_description) is str:
            text += f'**{class_brief_description}**\n'

        text += "## Description\n"

        if type(class_description) is str:
            text += class_description + '\n'

        methods_and_members = get_class_methods_and_members(class_list, class_list_index, class_name)
        #  sorted(methods_and_members["members"]
        members = sorted(methods_and_members["members"], key=lambda x: x["name"])
        methods = sorted(methods_and_members["methods"], key=lambda x: x["name"])

        if len(members) > 0:
            text += "## Properties\n"
            text += "|Type|Name|Default Value|\n|-|-|-|\n"

            for member in members:

                type_text = f'[{member["type"]}]'
                if member["type"] in class_list_index:
                    type_text += f'({wiki_root + member["type"]})'
                else:
                    type_text += f'({godot_wiki_root + member["type"].lower()}.html)'
                
                
                text += f'|{type_text} | [{member["name"]}](#{member["type"]}-{member["name"]}) |'
                if member["default"]:
                    text += f'`{member["default"]}`|\n'
                else:
                    text += "|\n"
                

        if len(methods) > 0:
            text += "## Methods\n"
            text += "|Return Type|Name|\n|-|-|\n"

            for method in methods:
                type_text = f'[{method["type"]}]'
                if method["type"] in class_list_index:
                    type_text += f'({wiki_root + method["type"]})'
                elif method["type"] == "void":
                    type_text = "void"
                else:
                    type_text += f'({godot_wiki_root + method["type"].lower()}.html)'
                
                name_text = f'[{method["name"]}](#{method["type"].lower()}-{method["name"]}-'

                argument_text = "  "
                if len(method["params"]) > 0:
                    argument_text = ""
                    name_text = name_text[:-1]
                    for param in method["params"]:
                        name_text += f'{param["name"]}-{param["type"].lower()}-'

                        param_type_text = f'[{param["type"]}]'
                        if param["type"] in class_list_index:
                            param_type_text += f'({wiki_root + param["type"]})'
                        elif param["type"] == "void":
                            param_type_text = "void"
                        else:
                            param_type_text += f'({godot_wiki_root + param["type"].lower()}.html)'
                        argument_text += f'{param["name"]}: {param_type_text}, '

                name_text = name_text[:-1] + ')'

                text += f'|{type_text}|{name_text}({argument_text[:-2]})|\n'

        text += "---\n"
        
        if len(members) > 0:
            text += "## Property Descriptions\n"
            for member in members:
                type_text = f'[`{member["type"]}`]'
                if member["type"] in class_list_index:
                    type_text += f'({wiki_root + member["type"]})'
                elif member["type"] == "void":
                    type_text = "void"
                else:
                    type_text += f'({godot_wiki_root + member["type"].lower()}.html)'

                text += f'### {type_text} `{member["name"]}`\n'

                property_description = member["description"]

                if type(property_description) is str:
                    text += property_description + '\n'
                
        if len(methods) > 0:
            text += "## Method Descriptions\n"
            for method in methods:
                type_text = f'[`{method["type"]}`]'
                if method["type"] in class_list_index:
                    type_text += f'({wiki_root + method["type"]})'
                elif method["type"] == "void":
                    type_text = "`void`"
                else:
                    type_text += f'({godot_wiki_root + method["type"].lower()}.html)'

                argument_text = "  "
                if len(method["params"]) > 0:
                    argument_text = ""
                    for param in method["params"]:
                        param_type_text = f'[{param["type"]}]'
                        if param["type"] in class_list_index:
                            param_type_text += f'({wiki_root + param["type"]})'
                        elif param["type"] == "void":
                            param_type_text = "void"
                        else:
                            param_type_text += f'({godot_wiki_root + param["type"].lower()}.html)'
                        argument_text += f'{param["name"]}: {param_type_text}, '

                text += f'### {type_text} <tt>{method["name"]}({argument_text[:-2]})</tt>  \n'

                property_description = method["description"]

                if type(property_description) is str:
                    text += property_description + '\n'
                text += "\n\n---\n"
            

        f = open("./github_wiki_md/" + file_names[file_index][:-4] + ".md", "w")
        f.write(text)
        f.close()
  
        file_index += 1
