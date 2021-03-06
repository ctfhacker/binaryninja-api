// Copyright (c) 2015-2017 Vector 35 LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#ifdef BINARYNINJACORE_LIBRARY
#include "type.h"
#else
#include "binaryninjaapi.h"
#endif

#ifdef BINARYNINJACORE_LIBRARY
namespace BinaryNinjaCore
#else
namespace BinaryNinja
#endif
{
#ifdef BINARYNINJACORE_LIBRARY
	typedef size_t ExprId;
#endif

	class LowLevelILFunction;

	template <BNLowLevelILOperation N>
	struct LowLevelILInstructionAccessor {};

	struct LowLevelILInstruction;
	struct LowLevelILConstantInstruction;
	struct LowLevelILOneOperandInstruction;
	struct LowLevelILTwoOperandInstruction;
	struct LowLevelILTwoOperandWithCarryInstruction;
	struct LowLevelILDoublePrecisionInstruction;
	struct LowLevelILLabel;
	struct MediumLevelILInstruction;
	class LowLevelILOperand;
	class LowLevelILOperandList;

	struct SSARegister
	{
		uint32_t reg;
		size_t version;

		SSARegister();
		SSARegister(uint32_t r, size_t i);
		SSARegister(const SSARegister& v);

		SSARegister& operator=(const SSARegister& v);
		bool operator==(const SSARegister& v) const;
		bool operator!=(const SSARegister& v) const;
		bool operator<(const SSARegister& v) const;
	};

	struct SSAFlag
	{
		uint32_t flag;
		size_t version;

		SSAFlag();
		SSAFlag(uint32_t f, size_t i);
		SSAFlag(const SSAFlag& v);

		SSAFlag& operator=(const SSAFlag& v);
		bool operator==(const SSAFlag& v) const;
		bool operator!=(const SSAFlag& v) const;
		bool operator<(const SSAFlag& v) const;
	};

	enum LowLevelILOperandType
	{
		IntegerLowLevelOperand,
		IndexLowLevelOperand,
		ExprLowLevelOperand,
		RegisterLowLevelOperand,
		FlagLowLevelOperand,
		FlagConditionLowLevelOperand,
		SSARegisterLowLevelOperand,
		SSAFlagLowLevelOperand,
		IndexListLowLevelOperand,
		SSARegisterListLowLevelOperand,
		SSAFlagListLowLevelOperand
	};

	enum LowLevelILOperandUsage
	{
		SourceExprLowLevelOperandUsage,
		SourceRegisterLowLevelOperandUsage,
		SourceFlagLowLevelOperandUsage,
		SourceSSARegisterLowLevelOperandUsage,
		SourceSSAFlagLowLevelOperandUsage,
		DestExprLowLevelOperandUsage,
		DestRegisterLowLevelOperandUsage,
		DestFlagLowLevelOperandUsage,
		DestSSARegisterLowLevelOperandUsage,
		DestSSAFlagLowLevelOperandUsage,
		PartialRegisterLowLevelOperandUsage,
		StackSSARegisterLowLevelOperandUsage,
		StackMemoryVersionLowLevelOperandUsage,
		LeftExprLowLevelOperandUsage,
		RightExprLowLevelOperandUsage,
		CarryExprLowLevelOperandUsage,
		HighExprLowLevelOperandUsage,
		LowExprLowLevelOperandUsage,
		ConditionExprLowLevelOperandUsage,
		HighRegisterLowLevelOperandUsage,
		HighSSARegisterLowLevelOperandUsage,
		LowRegisterLowLevelOperandUsage,
		LowSSARegisterLowLevelOperandUsage,
		ConstantLowLevelOperandUsage,
		VectorLowLevelOperandUsage,
		StackAdjustmentLowLevelOperandUsage,
		TargetLowLevelOperandUsage,
		TrueTargetLowLevelOperandUsage,
		FalseTargetLowLevelOperandUsage,
		BitIndexLowLevelOperandUsage,
		SourceMemoryVersionLowLevelOperandUsage,
		DestMemoryVersionLowLevelOperandUsage,
		FlagConditionLowLevelOperandUsage,
		OutputSSARegistersLowLevelOperandUsage,
		OutputMemoryVersionLowLevelOperandUsage,
		ParameterSSARegistersLowLevelOperandUsage,
		SourceSSARegistersLowLevelOperandUsage,
		SourceSSAFlagsLowLevelOperandUsage,
		SourceMemoryVersionsLowLevelOperandUsage,
		TargetListLowLevelOperandUsage
	};
}

namespace std
{
#ifdef BINARYNINJACORE_LIBRARY
	template<> struct hash<BinaryNinjaCore::SSARegister>
#else
	template<> struct hash<BinaryNinja::SSARegister>
#endif
	{
#ifdef BINARYNINJACORE_LIBRARY
		typedef BinaryNinjaCore::SSARegister argument_type;
#else
		typedef BinaryNinja::SSARegister argument_type;
#endif
		typedef uint64_t result_type;
		result_type operator()(argument_type const& value) const
		{
			return ((result_type)value.reg) ^ ((result_type)value.version << 32);
		}
	};

#ifdef BINARYNINJACORE_LIBRARY
	template<> struct hash<BinaryNinjaCore::SSAFlag>
#else
	template<> struct hash<BinaryNinja::SSAFlag>
#endif
	{
#ifdef BINARYNINJACORE_LIBRARY
		typedef BinaryNinjaCore::SSAFlag argument_type;
#else
		typedef BinaryNinja::SSAFlag argument_type;
#endif
		typedef uint64_t result_type;
		result_type operator()(argument_type const& value) const
		{
			return ((result_type)value.flag) ^ ((result_type)value.version << 32);
		}
	};

	template<> struct hash<BNLowLevelILOperation>
	{
		typedef BNLowLevelILOperation argument_type;
		typedef int result_type;
		result_type operator()(argument_type const& value) const
		{
			return (result_type)value;
		}
	};

#ifdef BINARYNINJACORE_LIBRARY
	template<> struct hash<BinaryNinjaCore::LowLevelILOperandUsage>
#else
	template<> struct hash<BinaryNinja::LowLevelILOperandUsage>
#endif
	{
#ifdef BINARYNINJACORE_LIBRARY
		typedef BinaryNinjaCore::LowLevelILOperandUsage argument_type;
#else
		typedef BinaryNinja::LowLevelILOperandUsage argument_type;
#endif
		typedef int result_type;
		result_type operator()(argument_type const& value) const
		{
			return (result_type)value;
		}
	};
}

#ifdef BINARYNINJACORE_LIBRARY
namespace BinaryNinjaCore
#else
namespace BinaryNinja
#endif
{
	class LowLevelILInstructionAccessException: public std::exception
	{
	public:
		LowLevelILInstructionAccessException(): std::exception() {}
		virtual const char* what() const NOEXCEPT { return "invalid access to LLIL instruction"; }
	};

	class LowLevelILIntegerList
	{
		struct ListIterator
		{
#ifdef BINARYNINJACORE_LIBRARY
			LowLevelILFunction* function;
			const BNLowLevelILInstruction* instr;
#else
			Ref<LowLevelILFunction> function;
			BNLowLevelILInstruction instr;
#endif
			size_t operand, count;

			bool operator==(const ListIterator& a) const;
			bool operator!=(const ListIterator& a) const;
			bool operator<(const ListIterator& a) const;
			ListIterator& operator++();
			uint64_t operator*();
			LowLevelILFunction* GetFunction() const { return function; }
		};

		ListIterator m_start;

	public:
		typedef ListIterator const_iterator;

		LowLevelILIntegerList(LowLevelILFunction* func, const BNLowLevelILInstruction& instr, size_t count);

		const_iterator begin() const;
		const_iterator end() const;
		size_t size() const;
		uint64_t operator[](size_t i) const;

		operator std::vector<uint64_t>() const;
	};

	class LowLevelILIndexList
	{
		struct ListIterator
		{
			LowLevelILIntegerList::const_iterator pos;
			bool operator==(const ListIterator& a) const { return pos == a.pos; }
			bool operator!=(const ListIterator& a) const { return pos != a.pos; }
			bool operator<(const ListIterator& a) const { return pos < a.pos; }
			ListIterator& operator++() { ++pos; return *this; }
			size_t operator*();
		};

		LowLevelILIntegerList m_list;

	public:
		typedef ListIterator const_iterator;

		LowLevelILIndexList(LowLevelILFunction* func, const BNLowLevelILInstruction& instr, size_t count);

		const_iterator begin() const;
		const_iterator end() const;
		size_t size() const;
		size_t operator[](size_t i) const;

		operator std::vector<size_t>() const;
	};

	class LowLevelILSSARegisterList
	{
		struct ListIterator
		{
			LowLevelILIntegerList::const_iterator pos;
			bool operator==(const ListIterator& a) const { return pos == a.pos; }
			bool operator!=(const ListIterator& a) const { return pos != a.pos; }
			bool operator<(const ListIterator& a) const { return pos < a.pos; }
			ListIterator& operator++() { ++pos; ++pos; return *this; }
			const SSARegister operator*();
		};

		LowLevelILIntegerList m_list;

	public:
		typedef ListIterator const_iterator;

		LowLevelILSSARegisterList(LowLevelILFunction* func, const BNLowLevelILInstruction& instr, size_t count);

		const_iterator begin() const;
		const_iterator end() const;
		size_t size() const;
		const SSARegister operator[](size_t i) const;

		operator std::vector<SSARegister>() const;
	};

	class LowLevelILSSAFlagList
	{
		struct ListIterator
		{
			LowLevelILIntegerList::const_iterator pos;
			bool operator==(const ListIterator& a) const { return pos == a.pos; }
			bool operator!=(const ListIterator& a) const { return pos != a.pos; }
			bool operator<(const ListIterator& a) const { return pos < a.pos; }
			ListIterator& operator++() { ++pos; ++pos; return *this; }
			const SSAFlag operator*();
		};

		LowLevelILIntegerList m_list;

	public:
		typedef ListIterator const_iterator;

		LowLevelILSSAFlagList(LowLevelILFunction* func, const BNLowLevelILInstruction& instr, size_t count);

		const_iterator begin() const;
		const_iterator end() const;
		size_t size() const;
		const SSAFlag operator[](size_t i) const;

		operator std::vector<SSAFlag>() const;
	};

	struct LowLevelILInstructionBase: public BNLowLevelILInstruction
	{
#ifdef BINARYNINJACORE_LIBRARY
		LowLevelILFunction* function;
#else
		Ref<LowLevelILFunction> function;
#endif
		size_t exprIndex, instructionIndex;

		static std::unordered_map<LowLevelILOperandUsage, LowLevelILOperandType> operandTypeForUsage;
		static std::unordered_map<BNLowLevelILOperation,
			std::vector<LowLevelILOperandUsage>> operationOperandUsage;
		static std::unordered_map<BNLowLevelILOperation,
			std::unordered_map<LowLevelILOperandUsage, size_t>> operationOperandIndex;

		LowLevelILOperandList GetOperands() const;

		uint64_t GetRawOperandAsInteger(size_t operand) const;
		uint32_t GetRawOperandAsRegister(size_t operand) const;
		size_t GetRawOperandAsIndex(size_t operand) const;
		BNLowLevelILFlagCondition GetRawOperandAsFlagCondition(size_t operand) const;
		LowLevelILInstruction GetRawOperandAsExpr(size_t operand) const;
		SSARegister GetRawOperandAsSSARegister(size_t operand) const;
		SSAFlag GetRawOperandAsSSAFlag(size_t operand) const;
		LowLevelILIndexList GetRawOperandAsIndexList(size_t operand) const;
		LowLevelILSSARegisterList GetRawOperandAsSSARegisterList(size_t operand) const;
		LowLevelILSSAFlagList GetRawOperandAsSSAFlagList(size_t operand) const;

		void UpdateRawOperand(size_t operandIndex, ExprId value);
		void UpdateRawOperandAsSSARegisterList(size_t operandIndex, const std::vector<SSARegister>& regs);

		RegisterValue GetValue() const;
		PossibleValueSet GetPossibleValues() const;

		RegisterValue GetRegisterValue(uint32_t reg);
		RegisterValue GetRegisterValueAfter(uint32_t reg);
		PossibleValueSet GetPossibleRegisterValues(uint32_t reg);
		PossibleValueSet GetPossibleRegisterValuesAfter(uint32_t reg);
		RegisterValue GetFlagValue(uint32_t flag);
		RegisterValue GetFlagValueAfter(uint32_t flag);
		PossibleValueSet GetPossibleFlagValues(uint32_t flag);
		PossibleValueSet GetPossibleFlagValuesAfter(uint32_t flag);
		RegisterValue GetStackContents(int32_t offset, size_t len);
		RegisterValue GetStackContentsAfter(int32_t offset, size_t len);
		PossibleValueSet GetPossibleStackContents(int32_t offset, size_t len);
		PossibleValueSet GetPossibleStackContentsAfter(int32_t offset, size_t len);

		size_t GetSSAInstructionIndex() const;
		size_t GetNonSSAInstructionIndex() const;
		size_t GetSSAExprIndex() const;
		size_t GetNonSSAExprIndex() const;

		LowLevelILInstruction GetSSAForm() const;
		LowLevelILInstruction GetNonSSAForm() const;

		size_t GetMediumLevelILInstructionIndex() const;
		size_t GetMediumLevelILExprIndex() const;
		size_t GetMappedMediumLevelILInstructionIndex() const;
		size_t GetMappedMediumLevelILExprIndex() const;

		bool HasMediumLevelIL() const;
		bool HasMappedMediumLevelIL() const;
		MediumLevelILInstruction GetMediumLevelIL() const;
		MediumLevelILInstruction GetMappedMediumLevelIL() const;

		void Replace(ExprId expr);

		template <BNLowLevelILOperation N>
		LowLevelILInstructionAccessor<N>& As()
		{
			if (operation != N)
				throw LowLevelILInstructionAccessException();
			return *(LowLevelILInstructionAccessor<N>*)this;
		}
		LowLevelILOneOperandInstruction& AsOneOperand()
		{
			return *(LowLevelILOneOperandInstruction*)this;
		}
		LowLevelILTwoOperandInstruction& AsTwoOperand()
		{
			return *(LowLevelILTwoOperandInstruction*)this;
		}
		LowLevelILTwoOperandWithCarryInstruction& AsTwoOperandWithCarry()
		{
			return *(LowLevelILTwoOperandWithCarryInstruction*)this;
		}
		LowLevelILDoublePrecisionInstruction& AsDoublePrecision()
		{
			return *(LowLevelILDoublePrecisionInstruction*)this;
		}

		template <BNLowLevelILOperation N>
		const LowLevelILInstructionAccessor<N>& As() const
		{
			if (operation != N)
				throw LowLevelILInstructionAccessException();
			return *(const LowLevelILInstructionAccessor<N>*)this;
		}
		const LowLevelILConstantInstruction& AsConstant() const
		{
			return *(const LowLevelILConstantInstruction*)this;
		}
		const LowLevelILOneOperandInstruction& AsOneOperand() const
		{
			return *(const LowLevelILOneOperandInstruction*)this;
		}
		const LowLevelILTwoOperandInstruction& AsTwoOperand() const
		{
			return *(const LowLevelILTwoOperandInstruction*)this;
		}
		const LowLevelILTwoOperandWithCarryInstruction& AsTwoOperandWithCarry() const
		{
			return *(const LowLevelILTwoOperandWithCarryInstruction*)this;
		}
		const LowLevelILDoublePrecisionInstruction& AsDoublePrecision() const
		{
			return *(const LowLevelILDoublePrecisionInstruction*)this;
		}
	};

	struct LowLevelILInstruction: public LowLevelILInstructionBase
	{
		LowLevelILInstruction();
		LowLevelILInstruction(LowLevelILFunction* func, const BNLowLevelILInstruction& instr,
			size_t expr, size_t instrIdx);
		LowLevelILInstruction(const LowLevelILInstructionBase& instr);

		void VisitExprs(const std::function<bool(const LowLevelILInstruction& expr)>& func) const;

		ExprId CopyTo(LowLevelILFunction* dest) const;
		ExprId CopyTo(LowLevelILFunction* dest,
			const std::function<ExprId(const LowLevelILInstruction& subExpr)>& subExprHandler) const;

		// Templated accessors for instruction operands, use these for efficient access to a known instruction
		template <BNLowLevelILOperation N> LowLevelILInstruction GetSourceExpr() const { return As<N>().GetSourceExpr(); }
		template <BNLowLevelILOperation N> uint32_t GetSourceRegister() const { return As<N>().GetSourceRegister(); }
		template <BNLowLevelILOperation N> uint32_t GetSourceFlag() const { return As<N>().GetSourceFlag(); }
		template <BNLowLevelILOperation N> SSARegister GetSourceSSARegister() const { return As<N>().GetSourceSSARegister(); }
		template <BNLowLevelILOperation N> SSAFlag GetSourceSSAFlag() const { return As<N>().GetSourceSSAFlag(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetDestExpr() const { return As<N>().GetDestExpr(); }
		template <BNLowLevelILOperation N> uint32_t GetDestRegister() const { return As<N>().GetDestRegister(); }
		template <BNLowLevelILOperation N> uint32_t GetDestFlag() const { return As<N>().GetDestFlag(); }
		template <BNLowLevelILOperation N> SSARegister GetDestSSARegister() const { return As<N>().GetDestSSARegister(); }
		template <BNLowLevelILOperation N> SSAFlag GetDestSSAFlag() const { return As<N>().GetDestSSAFlag(); }
		template <BNLowLevelILOperation N> uint32_t GetPartialRegister() const { return As<N>().GetPartialRegister(); }
		template <BNLowLevelILOperation N> SSARegister GetStackSSARegister() const { return As<N>().GetStackSSARegister(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetLeftExpr() const { return As<N>().GetLeftExpr(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetRightExpr() const { return As<N>().GetRightExpr(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetCarryExpr() const { return As<N>().GetCarryExpr(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetHighExpr() const { return As<N>().GetHighExpr(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetLowExpr() const { return As<N>().GetLowExpr(); }
		template <BNLowLevelILOperation N> LowLevelILInstruction GetConditionExpr() const { return As<N>().GetConditionExpr(); }
		template <BNLowLevelILOperation N> uint32_t GetHighRegister() const { return As<N>().GetHighRegister(); }
		template <BNLowLevelILOperation N> SSARegister GetHighSSARegister() const { return As<N>().GetHighSSARegister(); }
		template <BNLowLevelILOperation N> uint32_t GetLowRegister() const { return As<N>().GetLowRegister(); }
		template <BNLowLevelILOperation N> SSARegister GetLowSSARegister() const { return As<N>().GetLowSSARegister(); }
		template <BNLowLevelILOperation N> int64_t GetConstant() const { return As<N>().GetConstant(); }
		template <BNLowLevelILOperation N> int64_t GetVector() const { return As<N>().GetVector(); }
		template <BNLowLevelILOperation N> size_t GetStackAdjustment() const { return As<N>().GetStackAdjustment(); }
		template <BNLowLevelILOperation N> size_t GetTarget() const { return As<N>().GetTarget(); }
		template <BNLowLevelILOperation N> size_t GetTrueTarget() const { return As<N>().GetTrueTarget(); }
		template <BNLowLevelILOperation N> size_t GetFalseTarget() const { return As<N>().GetFalseTarget(); }
		template <BNLowLevelILOperation N> size_t GetBitIndex() const { return As<N>().GetBitIndex(); }
		template <BNLowLevelILOperation N> size_t GetSourceMemoryVersion() const { return As<N>().GetSourceMemoryVersion(); }
		template <BNLowLevelILOperation N> size_t GetDestMemoryVersion() const { return As<N>().GetDestMemoryVersion(); }
		template <BNLowLevelILOperation N> BNLowLevelILFlagCondition GetFlagCondition() const { return As<N>().GetFlagCondition(); }
		template <BNLowLevelILOperation N> LowLevelILSSARegisterList GetOutputSSARegisters() const { return As<N>().GetOutputSSARegisters(); }
		template <BNLowLevelILOperation N> LowLevelILSSARegisterList GetParameterSSARegisters() const { return As<N>().GetParameterSSARegisters(); }
		template <BNLowLevelILOperation N> LowLevelILSSARegisterList GetSourceSSARegisters() const { return As<N>().GetSourceSSARegisters(); }
		template <BNLowLevelILOperation N> LowLevelILSSAFlagList GetSourceSSAFlags() const { return As<N>().GetSourceSSAFlags(); }
		template <BNLowLevelILOperation N> LowLevelILIndexList GetSourceMemoryVersions() const { return As<N>().GetSourceMemoryVersions(); }
		template <BNLowLevelILOperation N> LowLevelILIndexList GetTargetList() const { return As<N>().GetTargetList(); }

		template <BNLowLevelILOperation N> void SetDestSSAVersion(size_t version) { As<N>().SetDestSSAVersion(version); }
		template <BNLowLevelILOperation N> void SetSourceSSAVersion(size_t version) { As<N>().SetSourceSSAVersion(version); }
		template <BNLowLevelILOperation N> void SetHighSSAVersion(size_t version) { As<N>().SetHighSSAVersion(version); }
		template <BNLowLevelILOperation N> void SetLowSSAVersion(size_t version) { As<N>().SetLowSSAVersion(version); }
		template <BNLowLevelILOperation N> void SetStackSSAVersion(size_t version) { As<N>().SetStackSSAVersion(version); }
		template <BNLowLevelILOperation N> void SetDestMemoryVersion(size_t version) { As<N>().SetDestMemoryVersion(version); }
		template <BNLowLevelILOperation N> void SetSourceMemoryVersion(size_t version) { As<N>().SetSourceMemoryVersion(version); }
		template <BNLowLevelILOperation N> void SetOutputSSARegisters(const std::vector<SSARegister>& regs) { As<N>().SetOutputSSARegisters(regs); }
		template <BNLowLevelILOperation N> void SetParameterSSARegisters(const std::vector<SSARegister>& regs) { As<N>().SetParameterSSARegisters(regs); }

		bool GetOperandIndexForUsage(LowLevelILOperandUsage usage, size_t& operandIndex) const;

		// Generic accessors for instruction operands, these will throw a LowLevelILInstructionAccessException
		// on type mismatch. These are slower than the templated versions above.
		LowLevelILInstruction GetSourceExpr() const;
		uint32_t GetSourceRegister() const;
		uint32_t GetSourceFlag() const;
		SSARegister GetSourceSSARegister() const;
		SSAFlag GetSourceSSAFlag() const;
		LowLevelILInstruction GetDestExpr() const;
		uint32_t GetDestRegister() const;
		uint32_t GetDestFlag() const;
		SSARegister GetDestSSARegister() const;
		SSAFlag GetDestSSAFlag() const;
		uint32_t GetPartialRegister() const;
		SSARegister GetStackSSARegister() const;
		LowLevelILInstruction GetLeftExpr() const;
		LowLevelILInstruction GetRightExpr() const;
		LowLevelILInstruction GetCarryExpr() const;
		LowLevelILInstruction GetHighExpr() const;
		LowLevelILInstruction GetLowExpr() const;
		LowLevelILInstruction GetConditionExpr() const;
		uint32_t GetHighRegister() const;
		SSARegister GetHighSSARegister() const;
		uint32_t GetLowRegister() const;
		SSARegister GetLowSSARegister() const;
		int64_t GetConstant() const;
		int64_t GetVector() const;
		size_t GetStackAdjustment() const;
		size_t GetTarget() const;
		size_t GetTrueTarget() const;
		size_t GetFalseTarget() const;
		size_t GetBitIndex() const;
		size_t GetSourceMemoryVersion() const;
		size_t GetDestMemoryVersion() const;
		BNLowLevelILFlagCondition GetFlagCondition() const;
		LowLevelILSSARegisterList GetOutputSSARegisters() const;
		LowLevelILSSARegisterList GetParameterSSARegisters() const;
		LowLevelILSSARegisterList GetSourceSSARegisters() const;
		LowLevelILSSAFlagList GetSourceSSAFlags() const;
		LowLevelILIndexList GetSourceMemoryVersions() const;
		LowLevelILIndexList GetTargetList() const;
	};

	class LowLevelILOperand
	{
		LowLevelILInstruction m_instr;
		LowLevelILOperandUsage m_usage;
		LowLevelILOperandType m_type;
		size_t m_operandIndex;

	public:
		LowLevelILOperand(const LowLevelILInstruction& instr, LowLevelILOperandUsage usage,
			size_t operandIndex);

		LowLevelILOperandType GetType() const { return m_type; }
		LowLevelILOperandUsage GetUsage() const { return m_usage; }

		uint64_t GetInteger() const;
		size_t GetIndex() const;
		LowLevelILInstruction GetExpr() const;
		uint32_t GetRegister() const;
		uint32_t GetFlag() const;
		BNLowLevelILFlagCondition GetFlagCondition() const;
		SSARegister GetSSARegister() const;
		SSAFlag GetSSAFlag() const;
		LowLevelILIndexList GetIndexList() const;
		LowLevelILSSARegisterList GetSSARegisterList() const;
		LowLevelILSSAFlagList GetSSAFlagList() const;
	};

	class LowLevelILOperandList
	{
		struct ListIterator
		{
			const LowLevelILOperandList* owner;
			std::vector<LowLevelILOperandUsage>::const_iterator pos;
			bool operator==(const ListIterator& a) const { return pos == a.pos; }
			bool operator!=(const ListIterator& a) const { return pos != a.pos; }
			bool operator<(const ListIterator& a) const { return pos < a.pos; }
			ListIterator& operator++() { ++pos; return *this; }
			const LowLevelILOperand operator*();
		};

		LowLevelILInstruction m_instr;
		const std::vector<LowLevelILOperandUsage>& m_usageList;
		const std::unordered_map<LowLevelILOperandUsage, size_t>& m_operandIndexMap;

	public:
		typedef ListIterator const_iterator;

		LowLevelILOperandList(const LowLevelILInstruction& instr,
			const std::vector<LowLevelILOperandUsage>& usageList,
			const std::unordered_map<LowLevelILOperandUsage, size_t>& operandIndexMap);

		const_iterator begin() const;
		const_iterator end() const;
		size_t size() const;
		const LowLevelILOperand operator[](size_t i) const;

		operator std::vector<LowLevelILOperand>() const;
	};

	struct LowLevelILConstantInstruction: public LowLevelILInstructionBase
	{
		int64_t GetConstant() const { return GetRawOperandAsInteger(0); }
	};

	struct LowLevelILOneOperandInstruction: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(0); }
	};

	struct LowLevelILTwoOperandInstruction: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetLeftExpr() const { return GetRawOperandAsExpr(0); }
		LowLevelILInstruction GetRightExpr() const { return GetRawOperandAsExpr(1); }
	};

	struct LowLevelILTwoOperandWithCarryInstruction: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetLeftExpr() const { return GetRawOperandAsExpr(0); }
		LowLevelILInstruction GetRightExpr() const { return GetRawOperandAsExpr(1); }
		LowLevelILInstruction GetCarryExpr() const { return GetRawOperandAsExpr(2); }
	};

	struct LowLevelILDoublePrecisionInstruction: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetHighExpr() const { return GetRawOperandAsExpr(0); }
		LowLevelILInstruction GetLowExpr() const { return GetRawOperandAsExpr(1); }
		LowLevelILInstruction GetRightExpr() const { return GetRawOperandAsExpr(2); }
	};

	// Implementations of each instruction to fetch the correct operand value for the valid operands, these
	// are derived from LowLevelILInstructionBase so that invalid operand accessor functions will generate
	// a compiler error.
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_REG>: public LowLevelILInstructionBase
	{
		uint32_t GetDestRegister() const { return GetRawOperandAsRegister(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_REG_SPLIT>: public LowLevelILInstructionBase
	{
		uint32_t GetHighRegister() const { return GetRawOperandAsRegister(0); }
		uint32_t GetLowRegister() const { return GetRawOperandAsRegister(1); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(2); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_REG_SSA>: public LowLevelILInstructionBase
	{
		SSARegister GetDestSSARegister() const { return GetRawOperandAsSSARegister(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(2); }
		void SetDestSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_REG_SSA_PARTIAL>: public LowLevelILInstructionBase
	{
		SSARegister GetDestSSARegister() const { return GetRawOperandAsSSARegister(0); }
		uint32_t GetPartialRegister() const { return GetRawOperandAsRegister(2); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(3); }
		void SetDestSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_REG_SPLIT_SSA>: public LowLevelILInstructionBase
	{
		SSARegister GetHighSSARegister() const { return GetRawOperandAsExpr(0).GetRawOperandAsSSARegister(0); }
		SSARegister GetLowSSARegister() const { return GetRawOperandAsExpr(1).GetRawOperandAsSSARegister(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(2); }
		void SetHighSSAVersion(size_t version) { GetRawOperandAsExpr(0).UpdateRawOperand(1, version); }
		void SetLowSSAVersion(size_t version) { GetRawOperandAsExpr(1).UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_FLAG>: public LowLevelILInstructionBase
	{
		uint32_t GetDestFlag() const { return GetRawOperandAsRegister(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SET_FLAG_SSA>: public LowLevelILInstructionBase
	{
		SSAFlag GetDestSSAFlag() const { return GetRawOperandAsSSAFlag(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(2); }
		void SetDestSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_LOAD>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_LOAD_SSA>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(0); }
		size_t GetSourceMemoryVersion() const { return GetRawOperandAsIndex(1); }
		void SetSourceMemoryVersion(size_t version) { UpdateRawOperand(1, version); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_STORE>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_STORE_SSA>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
		size_t GetDestMemoryVersion() const { return GetRawOperandAsIndex(1); }
		size_t GetSourceMemoryVersion() const { return GetRawOperandAsIndex(2); }
		LowLevelILInstruction GetSourceExpr() const { return GetRawOperandAsExpr(3); }
		void SetDestMemoryVersion(size_t version) { UpdateRawOperand(1, version); }
		void SetSourceMemoryVersion(size_t version) { UpdateRawOperand(2, version); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_REG>: public LowLevelILInstructionBase
	{
		uint32_t GetSourceRegister() const { return GetRawOperandAsRegister(0); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_REG_SSA>: public LowLevelILInstructionBase
	{
		SSARegister GetSourceSSARegister() const { return GetRawOperandAsSSARegister(0); }
		void SetSourceSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_REG_SSA_PARTIAL>: public LowLevelILInstructionBase
	{
		SSARegister GetSourceSSARegister() const { return GetRawOperandAsSSARegister(0); }
		uint32_t GetPartialRegister() const { return GetRawOperandAsRegister(2); }
		void SetSourceSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG>: public LowLevelILInstructionBase
	{
		uint32_t GetSourceFlag() const { return GetRawOperandAsRegister(0); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG_BIT>: public LowLevelILInstructionBase
	{
		uint32_t GetSourceFlag() const { return GetRawOperandAsRegister(0); }
		size_t GetBitIndex() const { return GetRawOperandAsIndex(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG_SSA>: public LowLevelILInstructionBase
	{
		SSAFlag GetSourceSSAFlag() const { return GetRawOperandAsSSAFlag(0); }
		void SetSourceSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG_BIT_SSA>: public LowLevelILInstructionBase
	{
		SSAFlag GetSourceSSAFlag() const { return GetRawOperandAsSSAFlag(0); }
		size_t GetBitIndex() const { return GetRawOperandAsIndex(2); }
		void SetSourceSSAVersion(size_t version) { UpdateRawOperand(1, version); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_JUMP>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_JUMP_TO>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
		LowLevelILIndexList GetTargetList() const { return GetRawOperandAsIndexList(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_CALL>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_CALL_STACK_ADJUST>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
		size_t GetStackAdjustment() const { return (size_t)GetRawOperandAsInteger(1); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_RET>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(0); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_IF>: public LowLevelILInstructionBase
	{
		LowLevelILInstruction GetConditionExpr() const { return GetRawOperandAsExpr(0); }
		size_t GetTrueTarget() const { return GetRawOperandAsIndex(1); }
		size_t GetFalseTarget() const { return GetRawOperandAsIndex(2); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_GOTO>: public LowLevelILInstructionBase
	{
		size_t GetTarget() const { return GetRawOperandAsIndex(0); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG_COND>: public LowLevelILInstructionBase
	{
		BNLowLevelILFlagCondition GetFlagCondition() const { return GetRawOperandAsFlagCondition(0); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_TRAP>: public LowLevelILInstructionBase
	{
		int64_t GetVector() const { return GetRawOperandAsInteger(0); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_CALL_SSA>: public LowLevelILInstructionBase
	{
		LowLevelILSSARegisterList GetOutputSSARegisters() const { return GetRawOperandAsExpr(0).GetRawOperandAsSSARegisterList(1); }
		size_t GetDestMemoryVersion() const { return GetRawOperandAsExpr(0).GetRawOperandAsIndex(0); }
		LowLevelILInstruction GetDestExpr() const { return GetRawOperandAsExpr(1); }
		SSARegister GetStackSSARegister() const { return GetRawOperandAsExpr(2).GetRawOperandAsSSARegister(0); }
		size_t GetSourceMemoryVersion() const { return GetRawOperandAsExpr(2).GetRawOperandAsIndex(2); }
		LowLevelILSSARegisterList GetParameterSSARegisters() const { return GetRawOperandAsExpr(3).GetRawOperandAsSSARegisterList(0); }
		void SetDestMemoryVersion(size_t version) { GetRawOperandAsExpr(0).UpdateRawOperand(0, version); }
		void SetSourceMemoryVersion(size_t version) { GetRawOperandAsExpr(2).UpdateRawOperand(2, version); }
		void SetStackSSAVersion(size_t version) { GetRawOperandAsExpr(2).UpdateRawOperand(1, version); }
		void SetOutputSSARegisters(const std::vector<SSARegister>& regs) { GetRawOperandAsExpr(0).UpdateRawOperandAsSSARegisterList(1, regs); }
		void SetParameterSSARegisters(const std::vector<SSARegister>& regs) { GetRawOperandAsExpr(3).UpdateRawOperandAsSSARegisterList(0, regs); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_SYSCALL_SSA>: public LowLevelILInstructionBase
	{
		LowLevelILSSARegisterList GetOutputSSARegisters() const { return GetRawOperandAsExpr(0).GetRawOperandAsSSARegisterList(1); }
		size_t GetDestMemoryVersion() const { return GetRawOperandAsExpr(0).GetRawOperandAsIndex(0); }
		SSARegister GetStackSSARegister() const { return GetRawOperandAsExpr(1).GetRawOperandAsSSARegister(0); }
		size_t GetSourceMemoryVersion() const { return GetRawOperandAsExpr(1).GetRawOperandAsIndex(2); }
		LowLevelILSSARegisterList GetParameterSSARegisters() const { return GetRawOperandAsExpr(2).GetRawOperandAsSSARegisterList(0); }
		void SetDestMemoryVersion(size_t version) { GetRawOperandAsExpr(0).UpdateRawOperand(0, version); }
		void SetSourceMemoryVersion(size_t version) { GetRawOperandAsExpr(1).UpdateRawOperand(2, version); }
		void SetStackSSAVersion(size_t version) { GetRawOperandAsExpr(1).UpdateRawOperand(1, version); }
		void SetOutputSSARegisters(const std::vector<SSARegister>& regs) { GetRawOperandAsExpr(0).UpdateRawOperandAsSSARegisterList(1, regs); }
		void SetParameterSSARegisters(const std::vector<SSARegister>& regs) { GetRawOperandAsExpr(2).UpdateRawOperandAsSSARegisterList(0, regs); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_REG_PHI>: public LowLevelILInstructionBase
	{
		SSARegister GetDestSSARegister() const { return GetRawOperandAsSSARegister(0); }
		LowLevelILSSARegisterList GetSourceSSARegisters() const { return GetRawOperandAsSSARegisterList(2); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_FLAG_PHI>: public LowLevelILInstructionBase
	{
		SSAFlag GetDestSSAFlag() const { return GetRawOperandAsSSAFlag(0); }
		LowLevelILSSAFlagList GetSourceSSAFlags() const { return GetRawOperandAsSSAFlagList(2); }
	};
	template <> struct LowLevelILInstructionAccessor<LLIL_MEM_PHI>: public LowLevelILInstructionBase
	{
		size_t GetDestMemoryVersion() const { return GetRawOperandAsIndex(0); }
		LowLevelILIndexList GetSourceMemoryVersions() const { return GetRawOperandAsIndexList(1); }
	};

	template <> struct LowLevelILInstructionAccessor<LLIL_NOP>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_POP>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_NORET>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_SYSCALL>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_BP>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_UNDEF>: public LowLevelILInstructionBase {};
	template <> struct LowLevelILInstructionAccessor<LLIL_UNIMPL>: public LowLevelILInstructionBase {};

	template <> struct LowLevelILInstructionAccessor<LLIL_CONST>: public LowLevelILConstantInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CONST_PTR>: public LowLevelILConstantInstruction {};

	template <> struct LowLevelILInstructionAccessor<LLIL_ADD>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_SUB>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_AND>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_OR>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_XOR>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_LSL>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_LSR>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_ASR>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_ROL>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_ROR>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MUL>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MULU_DP>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MULS_DP>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_DIVU>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_DIVS>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MODU>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MODS>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_E>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_NE>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_SLT>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_ULT>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_SLE>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_ULE>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_SGE>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_UGE>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_SGT>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_CMP_UGT>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_TEST_BIT>: public LowLevelILTwoOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_ADD_OVERFLOW>: public LowLevelILTwoOperandInstruction {};

	template <> struct LowLevelILInstructionAccessor<LLIL_ADC>: public LowLevelILTwoOperandWithCarryInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_SBB>: public LowLevelILTwoOperandWithCarryInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_RLC>: public LowLevelILTwoOperandWithCarryInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_RRC>: public LowLevelILTwoOperandWithCarryInstruction {};

	template <> struct LowLevelILInstructionAccessor<LLIL_DIVU_DP>: public LowLevelILDoublePrecisionInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_DIVS_DP>: public LowLevelILDoublePrecisionInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MODU_DP>: public LowLevelILDoublePrecisionInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_MODS_DP>: public LowLevelILDoublePrecisionInstruction {};

	template <> struct LowLevelILInstructionAccessor<LLIL_PUSH>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_NEG>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_NOT>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_SX>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_ZX>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_LOW_PART>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_BOOL_TO_INT>: public LowLevelILOneOperandInstruction {};
	template <> struct LowLevelILInstructionAccessor<LLIL_UNIMPL_MEM>: public LowLevelILOneOperandInstruction {};
}
