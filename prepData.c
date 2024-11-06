static bool selectCommonType(SDataType* commonType, const SDataType* newType) {
  if (type1 < 0 || type1 >= TSDB_DATA_TYPE_MAX || type2 < 0 || type2 >= TSDB_DATA_TYPE_MAX) {
        return false;
    }
  if (commonType->type == TSDB_DATA_TYPE_NULL) {
      *commonType = *newType;
      return true;
  }
  if (newType->type == TSDB_DATA_TYPE_NULL) {
      return true;
  }

  if (commonType->type == newType->type) {
      if (commonType->bytes < newType->bytes) {
          commonType->bytes = newType->bytes;
      }
      return true;
  }
  int type1 = commonType->type;
  int type2 = newType->type;
  if (type1 > type2) {
      int temp = type1;
      type1 = type2;
      type2 = temp;
  }
  int8_t resultType = gConvertTypes[type1][type2];
  if (resultType == -1) {
      return false;
  } else if (resultType == 0) {
      return false;
  } else {
      commonType->type = resultType;
      commonType->bytes = type_bytes[resultType];
      if (commonType->bytes == 0) {
          commonType->bytes = (commonType->bytes > newType->bytes) ? commonType->bytes : newType->bytes;
      }
      return true;
  }
}
