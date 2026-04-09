import bpy
import json
import os
import re
import ast

def _parse_value(value_str):
    value_str = value_str.strip()
    try:
        if '.' in value_str:
            return float(value_str)
        else:
            return int(value_str)
    except ValueError:
        pass

    if value_str.startswith('{') and value_str.endswith('}'):
        json_str = '[' + value_str[1:-1] + ']'
        json_str = json_str.replace('{', '[').replace('}', ']')
        try:
            return json.loads(json_str)
        except json.JSONDecodeError:
            pass

    try:
        return ast.literal_eval(value_str)
    except (ValueError, SyntaxError):
        pass

    return value_str

def parse_object_name(name):
    id_part = None
    gameobject_part = None
    flags_part = []
    link_target = None
    properties = {}

    double_hash = name.find('##')
    if double_hash != -1:
        before = name[:double_hash]
        if before.isdigit():
            id_part = int(before)
        after = name[double_hash+2:]
        first_hash = after.find('#')
        if first_hash != -1:
            gameobject_part = after[:first_hash]
            rest = after[first_hash:]

            matches = re.findall(r'#(\w+)(?::([^#]*))?', rest)
            for key, value in matches:
                if key.startswith('link'):
                    if value:
                        link_target = int(value)
                    else:
                        link_match = re.search(r'#link(\d+)', rest)
                        if link_match:
                            link_target = int(link_match.group(1))
                else:
                    if value == '':
                        flags_part.append(key)
                    else:
                        properties[key] = _parse_value(value)
        else:
            gameobject_part = after
    else:
        matches = re.findall(r'#(\w+)(?::([^#]*))?', name)
        for key, value in matches:
            if key.startswith('link'):
                if value:
                    link_target = int(value)
                else:
                    link_match = re.search(r'#link(\d+)', name)
                    if link_match:
                        link_target = int(link_match.group(1))
            else:
                if value == '':
                    flags_part.append(key)
                else:
                    properties[key] = _parse_value(value)

    return id_part, gameobject_part, flags_part, link_target, properties

def topological_sort(objects):
    obj_by_id = {obj['id']: obj for obj in objects if obj['id'] is not None}

    no_id = [obj for obj in objects if obj['id'] is None]

    visited = set()
    stack = set()
    order = []

    def dfs(node_id):
        if node_id in stack:
            return
        if node_id in visited:
            return
        visited.add(node_id)
        stack.add(node_id)
        obj = obj_by_id.get(node_id)
        if obj and obj['link'] is not None and obj['link'] in obj_by_id:
            dfs(obj['link'])
        stack.remove(node_id)
        order.append(obj)

    for obj in objects:
        if obj['id'] is not None and obj['id'] not in visited:
            dfs(obj['id'])

    # order.reverse()
    order.extend(no_id)
    return order

def export_scene(json_path):
    objects_raw = []

    for obj in bpy.context.scene.objects:
        if obj.type != 'MESH':
            continue

        pos = obj.matrix_world.to_translation()
        rot = obj.matrix_world.to_quaternion()
        scl = obj.matrix_world.to_scale()

        obj_id, gameobject, flags, link_target, properties = parse_object_name(obj.name)

        objects_raw.append({
            "name": obj.name,
            "id": obj_id,
            "gameobject": gameobject,
            "flags": flags,
            "properties": properties,
            "link": link_target,  
            "position": [pos.x, pos.y, pos.z],
            "rotation": [rot.x, rot.y, rot.z, rot.w],
            "scale": [scl.x, scl.y, scl.z],
        })


    objects_sorted = topological_sort(objects_raw)

    output = {"objects": objects_sorted}
    with open(json_path, "w") as f:
        json.dump(output, f, separators=(',', ':'), indent=None)

output_path = r"C:\Users\mquiniou\Documents\GitHub\frog-up-rising-of-heqet\res\Scene\Level1.json"
export_scene(output_path)