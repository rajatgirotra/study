# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: test.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='test.proto',
  package='test',
  syntax='proto2',
  serialized_pb=_b('\n\ntest.proto\x12\x04test\"/\n\x06Server\x12\x10\n\x08hostname\x18\x01 \x02(\t\x12\x13\n\x0b\x63redentials\x18\x02 \x02(\t\"\x84\x01\n\x0b\x45nvironment\x12\x0c\n\x04name\x18\x01 \x02(\t\x12$\n\x04type\x18\x02 \x02(\x0e\x32\x16.test.Environment.Type\x12\x1d\n\x07servers\x18\x03 \x03(\x0b\x32\x0c.test.Server\"\"\n\x04Type\x12\x07\n\x03UAT\x10\x00\x12\x07\n\x03\x44\x45V\x10\x01\x12\x08\n\x04PROD\x10\x02')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_ENVIRONMENT_TYPE = _descriptor.EnumDescriptor(
  name='Type',
  full_name='test.Environment.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='UAT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEV', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PROD', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=168,
  serialized_end=202,
)
_sym_db.RegisterEnumDescriptor(_ENVIRONMENT_TYPE)


_SERVER = _descriptor.Descriptor(
  name='Server',
  full_name='test.Server',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='hostname', full_name='test.Server.hostname', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='credentials', full_name='test.Server.credentials', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=20,
  serialized_end=67,
)


_ENVIRONMENT = _descriptor.Descriptor(
  name='Environment',
  full_name='test.Environment',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='test.Environment.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='type', full_name='test.Environment.type', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='servers', full_name='test.Environment.servers', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _ENVIRONMENT_TYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=70,
  serialized_end=202,
)

_ENVIRONMENT.fields_by_name['type'].enum_type = _ENVIRONMENT_TYPE
_ENVIRONMENT.fields_by_name['servers'].message_type = _SERVER
_ENVIRONMENT_TYPE.containing_type = _ENVIRONMENT
DESCRIPTOR.message_types_by_name['Server'] = _SERVER
DESCRIPTOR.message_types_by_name['Environment'] = _ENVIRONMENT

Server = _reflection.GeneratedProtocolMessageType('Server', (_message.Message,), dict(
  DESCRIPTOR = _SERVER,
  __module__ = 'test_pb2'
  # @@protoc_insertion_point(class_scope:test.Server)
  ))
_sym_db.RegisterMessage(Server)

Environment = _reflection.GeneratedProtocolMessageType('Environment', (_message.Message,), dict(
  DESCRIPTOR = _ENVIRONMENT,
  __module__ = 'test_pb2'
  # @@protoc_insertion_point(class_scope:test.Environment)
  ))
_sym_db.RegisterMessage(Environment)


# @@protoc_insertion_point(module_scope)