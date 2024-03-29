/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Hbase_types.h"

namespace apache { namespace hadoop { namespace hbase { namespace thrift {

const char* TCell::ascii_fingerprint = "1CCCF6FC31CFD1D61BBBB1BAF3590620";
const uint8_t TCell::binary_fingerprint[16] = {0x1C,0xCC,0xF6,0xFC,0x31,0xCF,0xD1,0xD6,0x1B,0xBB,0xB1,0xBA,0xF3,0x59,0x06,0x20};

uint32_t TCell::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TCell::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TCell");
  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->value);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->timestamp);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* ColumnDescriptor::ascii_fingerprint = "3B18638852FDF9DD911BC1174265F92E";
const uint8_t ColumnDescriptor::binary_fingerprint[16] = {0x3B,0x18,0x63,0x88,0x52,0xFD,0xF9,0xDD,0x91,0x1B,0xC1,0x17,0x42,0x65,0xF9,0x2E};

uint32_t ColumnDescriptor::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->maxVersions);
          this->__isset.maxVersions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->compression);
          this->__isset.compression = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->inMemory);
          this->__isset.inMemory = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->bloomFilterType);
          this->__isset.bloomFilterType = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->bloomFilterVectorSize);
          this->__isset.bloomFilterVectorSize = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->bloomFilterNbHashes);
          this->__isset.bloomFilterNbHashes = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->blockCacheEnabled);
          this->__isset.blockCacheEnabled = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 9:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->timeToLive);
          this->__isset.timeToLive = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ColumnDescriptor::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("ColumnDescriptor");
  xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->name);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("maxVersions", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->maxVersions);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("compression", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->compression);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("inMemory", ::apache::thrift::protocol::T_BOOL, 4);
  xfer += oprot->writeBool(this->inMemory);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("bloomFilterType", ::apache::thrift::protocol::T_STRING, 5);
  xfer += oprot->writeString(this->bloomFilterType);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("bloomFilterVectorSize", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->bloomFilterVectorSize);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("bloomFilterNbHashes", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->bloomFilterNbHashes);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("blockCacheEnabled", ::apache::thrift::protocol::T_BOOL, 8);
  xfer += oprot->writeBool(this->blockCacheEnabled);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("timeToLive", ::apache::thrift::protocol::T_I32, 9);
  xfer += oprot->writeI32(this->timeToLive);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TRegionInfo::ascii_fingerprint = "B58AB7A239831F8614F7B6709C89DC7B";
const uint8_t TRegionInfo::binary_fingerprint[16] = {0xB5,0x8A,0xB7,0xA2,0x39,0x83,0x1F,0x86,0x14,0xF7,0xB6,0x70,0x9C,0x89,0xDC,0x7B};

uint32_t TRegionInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->startKey);
          this->__isset.startKey = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->endKey);
          this->__isset.endKey = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->id);
          this->__isset.id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_BYTE) {
          xfer += iprot->readByte(this->version);
          this->__isset.version = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->serverName);
          this->__isset.serverName = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->port);
          this->__isset.port = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TRegionInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TRegionInfo");
  xfer += oprot->writeFieldBegin("startKey", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->startKey);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("endKey", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->endKey);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_I64, 3);
  xfer += oprot->writeI64(this->id);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 4);
  xfer += oprot->writeBinary(this->name);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("version", ::apache::thrift::protocol::T_BYTE, 5);
  xfer += oprot->writeByte(this->version);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("serverName", ::apache::thrift::protocol::T_STRING, 6);
  xfer += oprot->writeBinary(this->serverName);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("port", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->port);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* Mutation::ascii_fingerprint = "CD9E9D4A6406AD402C90440434AE18A0";
const uint8_t Mutation::binary_fingerprint[16] = {0xCD,0x9E,0x9D,0x4A,0x64,0x06,0xAD,0x40,0x2C,0x90,0x44,0x04,0x34,0xAE,0x18,0xA0};

uint32_t Mutation::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->isDelete);
          this->__isset.isDelete = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->column);
          this->__isset.column = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->writeToWAL);
          this->__isset.writeToWAL = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Mutation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Mutation");
  xfer += oprot->writeFieldBegin("isDelete", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->isDelete);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("column", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->column);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeBinary(this->value);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("writeToWAL", ::apache::thrift::protocol::T_BOOL, 4);
  xfer += oprot->writeBool(this->writeToWAL);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* BatchMutation::ascii_fingerprint = "4B8A4A9E051CAFF532E1C0D54F6AD2AB";
const uint8_t BatchMutation::binary_fingerprint[16] = {0x4B,0x8A,0x4A,0x9E,0x05,0x1C,0xAF,0xF5,0x32,0xE1,0xC0,0xD5,0x4F,0x6A,0xD2,0xAB};

uint32_t BatchMutation::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->row);
          this->__isset.row = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->mutations.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            iprot->readListBegin(_etype3, _size0);
            this->mutations.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += this->mutations[_i4].read(iprot);
            }
            iprot->readListEnd();
          }
          this->__isset.mutations = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t BatchMutation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("BatchMutation");
  xfer += oprot->writeFieldBegin("row", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->row);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("mutations", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->mutations.size()));
    std::vector<Mutation> ::const_iterator _iter5;
    for (_iter5 = this->mutations.begin(); _iter5 != this->mutations.end(); ++_iter5)
    {
      xfer += (*_iter5).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TIncrement::ascii_fingerprint = "5F9965D46A4F3845985AC0F9B81C3C69";
const uint8_t TIncrement::binary_fingerprint[16] = {0x5F,0x99,0x65,0xD4,0x6A,0x4F,0x38,0x45,0x98,0x5A,0xC0,0xF9,0xB8,0x1C,0x3C,0x69};

uint32_t TIncrement::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->table);
          this->__isset.table = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->row);
          this->__isset.row = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->column);
          this->__isset.column = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->ammount);
          this->__isset.ammount = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TIncrement::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TIncrement");
  xfer += oprot->writeFieldBegin("table", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->table);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("row", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->row);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("column", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeBinary(this->column);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("ammount", ::apache::thrift::protocol::T_I64, 4);
  xfer += oprot->writeI64(this->ammount);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TColumn::ascii_fingerprint = "53A78393C2EDF13B3E77589DF969E89A";
const uint8_t TColumn::binary_fingerprint[16] = {0x53,0xA7,0x83,0x93,0xC2,0xED,0xF1,0x3B,0x3E,0x77,0x58,0x9D,0xF9,0x69,0xE8,0x9A};

uint32_t TColumn::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->columnName);
          this->__isset.columnName = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->cell.read(iprot);
          this->__isset.cell = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TColumn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TColumn");
  xfer += oprot->writeFieldBegin("columnName", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->columnName);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("cell", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->cell.write(oprot);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TRowResult::ascii_fingerprint = "9A5547565643A177300AFED9A6BD175D";
const uint8_t TRowResult::binary_fingerprint[16] = {0x9A,0x55,0x47,0x56,0x56,0x43,0xA1,0x77,0x30,0x0A,0xFE,0xD9,0xA6,0xBD,0x17,0x5D};

uint32_t TRowResult::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->row);
          this->__isset.row = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->columns.clear();
            uint32_t _size6;
            ::apache::thrift::protocol::TType _ktype7;
            ::apache::thrift::protocol::TType _vtype8;
            iprot->readMapBegin(_ktype7, _vtype8, _size6);
            uint32_t _i10;
            for (_i10 = 0; _i10 < _size6; ++_i10)
            {
              Text _key11;
              xfer += iprot->readBinary(_key11);
              TCell& _val12 = this->columns[_key11];
              xfer += _val12.read(iprot);
            }
            iprot->readMapEnd();
          }
          this->__isset.columns = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->sortedColumns.clear();
            uint32_t _size13;
            ::apache::thrift::protocol::TType _etype16;
            iprot->readListBegin(_etype16, _size13);
            this->sortedColumns.resize(_size13);
            uint32_t _i17;
            for (_i17 = 0; _i17 < _size13; ++_i17)
            {
              xfer += this->sortedColumns[_i17].read(iprot);
            }
            iprot->readListEnd();
          }
          this->__isset.sortedColumns = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TRowResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TRowResult");
  xfer += oprot->writeFieldBegin("row", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->row);
  xfer += oprot->writeFieldEnd();
  if (this->__isset.columns) {
    xfer += oprot->writeFieldBegin("columns", ::apache::thrift::protocol::T_MAP, 2);
    {
      xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->columns.size()));
      std::map<Text, TCell> ::const_iterator _iter18;
      for (_iter18 = this->columns.begin(); _iter18 != this->columns.end(); ++_iter18)
      {
        xfer += oprot->writeBinary(_iter18->first);
        xfer += _iter18->second.write(oprot);
      }
      xfer += oprot->writeMapEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.sortedColumns) {
    xfer += oprot->writeFieldBegin("sortedColumns", ::apache::thrift::protocol::T_LIST, 3);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->sortedColumns.size()));
      std::vector<TColumn> ::const_iterator _iter19;
      for (_iter19 = this->sortedColumns.begin(); _iter19 != this->sortedColumns.end(); ++_iter19)
      {
        xfer += (*_iter19).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TScan::ascii_fingerprint = "059961D32A9F4C6CAEBA0C5FE27A5B71";
const uint8_t TScan::binary_fingerprint[16] = {0x05,0x99,0x61,0xD3,0x2A,0x9F,0x4C,0x6C,0xAE,0xBA,0x0C,0x5F,0xE2,0x7A,0x5B,0x71};

uint32_t TScan::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->startRow);
          this->__isset.startRow = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->stopRow);
          this->__isset.stopRow = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->columns.clear();
            uint32_t _size20;
            ::apache::thrift::protocol::TType _etype23;
            iprot->readListBegin(_etype23, _size20);
            this->columns.resize(_size20);
            uint32_t _i24;
            for (_i24 = 0; _i24 < _size20; ++_i24)
            {
              xfer += iprot->readBinary(this->columns[_i24]);
            }
            iprot->readListEnd();
          }
          this->__isset.columns = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->caching);
          this->__isset.caching = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->filterString);
          this->__isset.filterString = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->sortColumns);
          this->__isset.sortColumns = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TScan::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TScan");
  if (this->__isset.startRow) {
    xfer += oprot->writeFieldBegin("startRow", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeBinary(this->startRow);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.stopRow) {
    xfer += oprot->writeFieldBegin("stopRow", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeBinary(this->stopRow);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.timestamp) {
    xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_I64, 3);
    xfer += oprot->writeI64(this->timestamp);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.columns) {
    xfer += oprot->writeFieldBegin("columns", ::apache::thrift::protocol::T_LIST, 4);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->columns.size()));
      std::vector<Text> ::const_iterator _iter25;
      for (_iter25 = this->columns.begin(); _iter25 != this->columns.end(); ++_iter25)
      {
        xfer += oprot->writeBinary((*_iter25));
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.caching) {
    xfer += oprot->writeFieldBegin("caching", ::apache::thrift::protocol::T_I32, 5);
    xfer += oprot->writeI32(this->caching);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.filterString) {
    xfer += oprot->writeFieldBegin("filterString", ::apache::thrift::protocol::T_STRING, 6);
    xfer += oprot->writeBinary(this->filterString);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.sortColumns) {
    xfer += oprot->writeFieldBegin("sortColumns", ::apache::thrift::protocol::T_BOOL, 7);
    xfer += oprot->writeBool(this->sortColumns);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* IOError::ascii_fingerprint = "EFB929595D312AC8F305D5A794CFEDA1";
const uint8_t IOError::binary_fingerprint[16] = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

uint32_t IOError::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t IOError::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("IOError");
  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->message);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* IllegalArgument::ascii_fingerprint = "EFB929595D312AC8F305D5A794CFEDA1";
const uint8_t IllegalArgument::binary_fingerprint[16] = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

uint32_t IllegalArgument::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t IllegalArgument::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("IllegalArgument");
  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->message);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* AlreadyExists::ascii_fingerprint = "EFB929595D312AC8F305D5A794CFEDA1";
const uint8_t AlreadyExists::binary_fingerprint[16] = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

uint32_t AlreadyExists::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t AlreadyExists::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("AlreadyExists");
  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->message);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

}}}} // namespace
